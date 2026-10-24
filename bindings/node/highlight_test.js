const assert = require("node:assert/strict");
const { readFileSync, readdirSync } = require("node:fs");
const path = require("node:path");
const { test } = require("node:test");
const Parser = require("tree-sitter");
const language = require(".");
const root = path.resolve(__dirname, "../..");
const query = new Parser.Query(language, readFileSync(path.join(root, "queries/highlights.scm"), "utf8"));

// Resolve every matching pattern in query order, as last-wins consumers do.
// Checking every position also catches a broad capture masking a nested escape.
for (const file of readdirSync(path.join(root, "test/highlights"))) {
  test(`last-wins highlights: ${file}`, () => {
    const fixture = JSON.parse(readFileSync(path.join(root, "test/highlights", file), "utf8"));
    const parser = new Parser();
    parser.setLanguage(language);
    const tree = parser.parse(fixture.source);
    assert.equal(tree.rootNode.hasError, false, tree.rootNode.toString());
    const captures = new Array(fixture.source.length);
    const matches = query.matches(tree.rootNode).sort((a, b) => a.pattern - b.pattern);
    for (const match of matches) {
      for (const { name, node } of match.captures) {
        if (!name.startsWith("_")) captures.fill(name, node.startIndex, node.endIndex);
      }
    }
    for (const expected of fixture.captures) {
      let start = -1;
      for (let i = 0; i <= (expected.occurrence ?? 0); i++) {
        start = fixture.source.indexOf(expected.text, start + 1);
        assert.notEqual(start, -1, `Missing fixture text: ${expected.text}`);
      }
      for (let i = start; i < start + expected.text.length; i++) {
        assert.equal(captures[i], expected.capture, `${file}: ${expected.text} at ${i}`);
      }
    }
  });
}

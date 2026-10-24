# Contributing

Report parser and highlighting issues with a minimal `.bmx` example, expected
behavior and the Tree-sitter version. Editor configuration issues belong in the
relevant editor extension repository. Maintenance includes reviewing issues and
pull requests regularly; the maintainer remains responsible for that ongoing work.

Use Conventional Commits, such as `fix: correct directive highlighting` or
`feat: parse a new language construct`. Follow semantic versioning: increment
the major version for breaking changes, minor for added functionality and patch
for bug fixes. Keep versions in `tree-sitter.json`, `package.json`, `Cargo.toml`,
`CMakeLists.txt`, `Makefile` and `pyproject.toml` synchronized.

Run `pnpm generate`, `pnpm test` and `cargo test` before submitting changes.
Use Tree-sitter CLI 0.25.10 and ABI 14 for generation. Commit the generated parser
sources with grammar changes. CI additionally checks query formatting and
cross-platform native builds.

Add corpus cases for syntax changes and expected captures under `test/highlights/`
for highlighting changes. Capture fixtures identify a token, its zero-based
occurrence and its expected highlight. Their Node test applies all matching
patterns in query order, with the last pattern taking precedence. Put generic
rules before specific rules and use standard Tree-sitter or Neovim capture names.

Release and dependency-regeneration workflows reuse the official Tree-sitter
workflows. Release builds use the committed parser and ABI 14. Package registry
publishing is not enabled; pushing a version tag creates a GitHub release.

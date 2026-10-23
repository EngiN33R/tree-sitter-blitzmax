import XCTest
import SwiftTreeSitter
import TreeSitterBlitzmax

final class TreeSitterBlitzmaxTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_blitzmax())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading Blitzmax grammar")
    }
}

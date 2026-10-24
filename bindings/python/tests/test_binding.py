from unittest import TestCase

from tree_sitter import Language, Parser, Query
import tree_sitter_blitzmax


class TestLanguage(TestCase):
    def test_can_load_grammar(self):
        Parser(Language(tree_sitter_blitzmax.language()))

    def test_packaged_highlights_are_available(self):
        query = tree_sitter_blitzmax.HIGHLIGHTS_QUERY
        self.assertIn("@keyword.directive", query)
        Query(Language(tree_sitter_blitzmax.language()), query)
        self.assertIn("HIGHLIGHTS_QUERY", dir(tree_sitter_blitzmax))
        with self.assertRaises(AttributeError):
            getattr(tree_sitter_blitzmax, "UNKNOWN_QUERY")

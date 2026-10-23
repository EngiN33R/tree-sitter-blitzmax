package tree_sitter_blitzmax_test

import (
	"testing"

	tree_sitter "github.com/tree-sitter/go-tree-sitter"
	tree_sitter_blitzmax "github.com/engin33r/tree-sitter-blitzmax/bindings/go"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_blitzmax.Language())
	if language == nil {
		t.Errorf("Error loading Blitzmax grammar")
	}
}

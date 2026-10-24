"""Case-insensitive Tree-sitter grammar for BlitzMax NG."""

from importlib.resources import files as _files

from ._binding import language


def __getattr__(name):
    if name == "HIGHLIGHTS_QUERY":
        query = _files(__package__) / "queries" / "highlights.scm"
        globals()[name] = query.read_text(encoding="utf-8")
        return globals()[name]
    raise AttributeError(f"module {__name__!r} has no attribute {name!r}")


__all__ = ["language", "HIGHLIGHTS_QUERY"]


def __dir__():
    return sorted(set(globals()) | set(__all__))

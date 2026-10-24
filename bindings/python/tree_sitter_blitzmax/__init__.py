"""Case-insensitive Tree-sitter grammar for BlitzMax NG."""

from importlib.resources import files as _files
from pathlib import Path as _Path

from ._binding import language


def __getattr__(name):
    if name == "HIGHLIGHTS_QUERY":
        query = _files(__package__) / "queries" / "highlights.scm"
        # Editable installs import from bindings/python instead of the wheel's
        # package directory. In that layout, read the checkout's source query.
        package_dir = _Path(__file__).resolve().parent
        if (not query.is_file() and package_dir.parent.name == "python"
                and package_dir.parent.parent.name == "bindings"):
            query = package_dir.parents[2] / "queries" / "highlights.scm"
        globals()[name] = query.read_text(encoding="utf-8")
        return globals()[name]
    raise AttributeError(f"module {__name__!r} has no attribute {name!r}")


__all__ = ["language", "HIGHLIGHTS_QUERY"]


def __dir__():
    return sorted(set(globals()) | set(__all__))

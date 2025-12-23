"""GDB pretty-printers for cub3d types
Place this file in the workspace root at .vscode/gdb_pretty_printers.py
Importing this module registers printers that make the VS Code Variables panel
show human-friendly representations for `t_map`, `char **` (grid) and `t_node`.
"""

import gdb
import gdb.printing

def _safe_int(val):
    try:
        return int(val)
    except Exception:
        return 0

class TMapPrinter:
    """Pretty-printer for `t_map`"""
    def __init__(self, val):
        self.val = val

    def to_string(self):
        w = _safe_int(self.val['width'])
        h = _safe_int(self.val['height'])
        return 't_map(width=%d, height=%d)' % (w, h)

    def children(self):
        grid = self.val['grid']
        h = _safe_int(self.val['height'])
        for i in range(h):
            try:
                # grid is char **; (grid + i).dereference() is char *
                row_ptr = (grid + i).dereference()
                try:
                    row_str = row_ptr.string()
                except Exception:
                    row_str = '<non-null-terminated or inaccessible>'
            except Exception:
                row_str = '<invalid>'
            yield ('[%d]' % i, row_str)

    def display_hint(self):
        return 'map'

class CharPtrArrayPrinter:
    """Pretty-printer for `char **` arrays. Shows up to a limited number of rows."""
    def __init__(self, val):
        self.val = val

    def to_string(self):
        return 'char** @ %s' % (self.val)

    def children(self):
        max_show = 50
        for i in range(max_show):
            try:
                ptr = (self.val + i).dereference()
                if int(ptr) == 0:
                    break
                try:
                    s = ptr.string()
                except Exception:
                    s = '<non-null-terminated or inaccessible>'
            except Exception:
                break
            yield ('[%d]' % i, s)

    def display_hint(self):
        return 'array'

class TNodePrinter:
    """Pretty-printer for linked list `t_node` - traverses next pointers and
    yields simple (x,y) entries."""
    def __init__(self, val):
        # Accept either t_node or t_node*
        self.val = val

    def to_string(self):
        try:
            addr = self.val.address
        except Exception:
            addr = self.val
        return 't_node @ %s' % (addr)

    def children(self):
        # If pointer, deref once
        node = self.val
        # handle pointer wrappers
        try:
            if node.type.code == gdb.TYPE_CODE_PTR:
                if int(node) == 0:
                    return
                node = node.dereference()
        except Exception:
            pass

        idx = 0
        while True:
            try:
                x = int(node['x'])
                y = int(node['y'])
                yield ('node[%d]' % idx, '(x=%d,y=%d)' % (x, y))
                next_ptr = node['next']
                if int(next_ptr) == 0:
                    break
                node = next_ptr.dereference()
            except Exception:
                break
            idx += 1

    def display_hint(self):
        return 'array'

# Collection to match by type name / regex
printer = gdb.printing.RegexpCollectionPrettyPrinter('cub3d')
printer.add_printer('t_map', '^t_map$', TMapPrinter)
printer.add_printer('char**', '^char \*\*$', CharPtrArrayPrinter)
printer.add_printer('t_node', '^t_node(\s*\*)?$', TNodePrinter)

def register_printers(objfile=None):
    try:
        gdb.printing.register_pretty_printer(objfile, printer)
    except Exception:
        # Fallback to global registration
        gdb.printing.register_pretty_printer(None, printer)

# Auto-register when imported
register_printers(None)

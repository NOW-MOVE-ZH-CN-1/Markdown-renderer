# md-renderer
Simple markdown renderer written in C++.
No class, pure function implementation.

## Supported syntax
- `# Heading 1`
- `## Heading 2`
- `**bold text**`
- `- unordered list`

## Build & Run
```bash
mkdir build && cd build
cmake ..
make
./md-renderer ../test.md

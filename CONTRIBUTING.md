# Contributing

Any contributions to the JamJarNative game engine are welcome, please review our [Code of Conduct](./CODE_OF_CONDUCT.md)
before making a contribution.

## Raising an Issue

Please follow one of the following templates for raising an issue against this project.

### Bug Report

Please use the bug report template for reporting a bug.

### Feature Request

Please use the feature request template for requesting a new feature.

### Requesting Help

Please use the [discussions](https://github.com/jamjarlabs/JamJarNative/discussions) to raise any requests for help or
general queries.

## Developing

Any code contributions are also welcome, please pick up an issue, if you can comment on it to reduce the chance of
duplicated effort that would be great.

### Dependencies

The project has the following dependencies:

- `cmake` == `3.16.X`
- `clang` == `11.1.X`
- `clang-tidy` == `11.1.X`
- `clang-format` == `11.1.X`
- `emscripten` == `2.0.X`

Later minor and patch versions of these dependencies should still work, the CI build just uses the versions above.

To view the docs locally, the project requires:

- `python` == `3.8.X`

To install the required pip dependencies to view the docs locally, run:

```bash
pip install -r docs/requirements.txt
```

### Starting

Outlined below are some steps for beginning development on different environments. These are not exhaustive, and only
show the absolute basics for getting set up.

#### Linux/MacOS

First install the dependencies [listed in the dependencies section](#dependencies), then you can run the following
command to generate the build system:

```bash
emcmake cmake -D CMAKE_EXPORT_COMPILE_COMMANDS=ON . -B build
```

This command will generate some build files in the `build/` directory, inside which you can run:

```bash
emmake make
```

This will generate the `build/libJamJarNative.a` library archive which can be used when building game executables.

##### Running unit tests

Run the unit tests by running the following in the `build/` directory:

```bash
ctest
```

##### Skipping unit test compilation

You can skip compiling unit tests by running this as your build system generation command:

```bash
emcmake cmake -D JAMJAR_NATIVE_COMPILE_UNIT_TESTS=OFF -D CMAKE_EXPORT_COMPILE_COMMANDS=ON -B build .
```

### Targets

The cmake is set up to provide a couple useful targets:

- `beautify` - runs `clang-format` against the codebase, must be run to pass the CI.
- `lint` - runs `clang-tidy` against the codebase, must be run to pass the CI.
- `lint_fix` - runs `clang-tidy` against the codebase and will attempt to fix the code (this may break things).
- `serve_docs` - hosts the docs locally on `http://localhost:8000`.

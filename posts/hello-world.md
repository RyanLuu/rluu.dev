Writing a static site generator is a fun little programming exercise, abound with creativity, personal touches, and tiny compilers. Today I'll tell you about the hardworking SSG that generated the post you're reading: **sausage**.

# About rluu.dev and me

I love reading blogs and have wanted one of my own for a long while. My main issue was "not having anything to write about," or more likely, not processing my hazy thoughts and fleeting experiences into something that could be written about.

Sausage was my way of bootstrapping this process. It's easy for me to start a coding project. If that project incentivizes me to write&mdash;how embarrassing would it be to build an SSG but no content to use it on&mdash;and also gives me something to write about, then that's what we call a two-for-one doorbuster, while supplies last.

# Tiny compilers

Static site generation really just involves translating your preferred languages to the web and automating tedious, error-prone tasks. In order to let you write in my preferred languages, Sausage contains four tiny compilers:

1. [`cmark`](https://github.com/commonmark/cmark) compiles Markdown to HTML
2. [`mustach`](https://gitlab.com/jobol/mustach) interprets Mustache template files to generate HTML and RSS
3. [`treesitter`](https://tree-sitter.github.io/tree-sitter/) parses any language for syntax highlighting
4. [`tomlc99`](https://github.com/cktan/tomlc99) parses the TOML configuration

In all of my choices, I wanted languages that were just barely strong enough to accomplish my goals, including sausage's source language, C. Go's [template language](https://pkg.go.dev/text/template) is really nice to work with, but I found Mustache to have just enough features for me. The `mustach` library didn't implement the optional inheritance module though, so I added that to my version.

Treesitter, however, sticks out as a particularly powerful language compared to what is typically used for syntax highlighting on the web: regex. I just can't stomach parsing a nonregular language with regexes, and a code snippet with [improper highlighting](https://prismjs.com/known-failures) would bother me to no end.

# What's next?

I hope for the direction of rluu.dev to inform the direction of sausage. That's the upside of writing it myself, right? That being said, there are some more general things on my mind:

- Configuration: It's common for SSGs to use a config file, but I don't see why I needed that here. I could just configure in C and rebuild when needed, freeing me from the constraints of a configuration language.
- Math: I don't want to dump MathJax onto visitors every time I want to render a little equation, so I might use the [texmath](https://github.com/jgm/texmath) Haskell library to generate MathML.
- Syntax highlighting: I use the treesitter library and manually style each language, but the treesitter maintainers do this for me with queries written in Scheme and a Rust library called [tree-sitter-highlight](https://github.com/tree-sitter/tree-sitter/tree/master/highlight).

So let's get some content into sausage because [xkcd](https://xkcd.com/1205/) is telling me I'll need a lot to recoup that time...


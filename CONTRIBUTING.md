# Contributing

Contributing is easy, just submit a pull request. Send me a email if you have any questions, I'm usually pretty prompt (russellgreene8 at gmail.com). 

## clang-format
I use `clang-format` to make sure code style is consistent. Run the `scripts/format_code.sh` script to run this. 

I use a pre-commit hook in git to run the formatter for me, run the `scripts/setup_hooks.sh` script to setup these for you. `clang-format` needs to be in `$PATH` for this to work, the script will fail (and not add the hook for you) if it isn't in `$PATH`.
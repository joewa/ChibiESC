# ChibiESC

[![Join the chat at https://gitter.im/joewa/ChibiESC](https://badges.gitter.im/joewa/ChibiESC.svg)](https://gitter.im/joewa/ChibiESC?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
Free electric speed controller software using ChibiOS

## Repository setup

You need to clone [our fork of pprzlink](https://github.com/heiko-r/pprzlink) into a directory next to this repo.

Before committing, please install the pre-commit hook: `ln -s ../../pre-commit .git/hooks/pre-commit`

It automatically adds a file containing the current branch and commit hash of the pprzlink repo when committing to ChibiESC.

If you want to place your pprzlink clone elsewhere, you need to fix your symlinks in the subsystems/pprzlink directory, the above-mentioned pre-commit hook and the INCDIR variable in the Makefile.

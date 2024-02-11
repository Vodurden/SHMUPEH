# SHMUPEH

This is a recovered version of my high school software project, a Shoot-Em-Up game. It was one of the first
C++ programs I wrote.

## Compiling

Run `make`. Dependencies are specified in `flake.nix`.

## Source Recovery

Source code was partially recovered from an old word document I found in my email. The remaining source code
had to be reconstructed from scratch, this included:

- `main.cpp`
- `EnemyWaveSpawner.h`
- `EnemyWaveSpawner.cpp`

For `EnemyWaveSpawner` we did know the fields that were used, but nothing else thanks to a table in the word document.

All imports were also missing, and have been reconstructed.

## Asset Recovery

All original asset files are lost, but most assets have been recovered from screenshots of the game. 

Assets that were completely lost and had to be recreated include:

- `explosion.png`
- All ship animations (a single image of each ship sprite was recoverable)
- All bullet animations (a single image of each bullet sprite was recoverabe)

## Changes from the original

Most bugs have been left intact, a few have been fixed because they are impacted by the loss of original assets:

1. The Animation system had an off-by-one error, this has been fixed.
2. The original game had SFML sprite-scaling enabled, which makes all the sprites blurry. This has been fixed.

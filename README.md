# mspacmab-retro current state of art

You must install to play: [gcc](https://gcc.gnu.org/), [imagemagick](https://imagemagick.org), [ghidra](https://ghidra-sre.org/) and maybe [rustup](https://rustup.rs/).

Use ghidra on `mspacmab_romram.gzf` file and help me if you can :-)

## mspacmab-retro installation

Drop the following files in current folder:

| md5sum                           | file      |
| -------------------------------- | --------- |
| de1d1d183af56cc3531d453ef1aa58b2 | 5e        |
| 9bd810182bc231c205eddc99281d3ba0 | 5f        |
| 80239848ef62294e0e78e33a3f444e9c | 82s123.7f |
| ccfe14e6f085cf7dc8cbeaabe33be586 | 82s126.1m |
| 726e495bf2562dee07ac463876bcc9a9 | 82s126.3m |
| e46a7be53fc919b1416be6451636ec9d | 82s126.4a |
| ea44a32231db2424e8ea402af869f766 | boot1     |
| ea0db5fb4fc9003ba4ac18b33bb1a9ba | boot2     |
| 2def9e970f78900a6a7dddd7c2c72aef | boot3     |
| aba661add0ffd90ba8fb026c54e06db8 | boot4     |
| 8393d99e0bcecd9d0fb5db5aefec93fc | boot5     |
| d796286df9a25e26309b770039a9010d | boot6     |


Run `extract-all.sh`

Resulting files:

- `mspacmab_data.rs` : all static *map*, *sprites* and *wavetables* usable with today tools
- `mspacmab_tile.png` and `mspacmab_sprite.png` for debug purpose
- `mspacmab_romram.bytes` ROM and RAM in _one_ file

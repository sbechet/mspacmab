use std::fs::File;
use std::io::BufWriter;

use riff_wave::{WaveWriter};

/// Namco 3-channel Wave Sound Generator wave data (8 waveforms with 32 4-bit entries each)
pub const WAVEDATA: [ [u8; 32]; 8] = [
    [7, 9, 10, 11, 12, 13, 13, 14, 14, 14, 13, 13, 12, 11, 10, 9, 7, 5, 4, 3, 2, 1, 1, 0, 0, 0, 1, 1, 2, 3, 4, 5, ],
    [7, 12, 14, 14, 13, 11, 9, 10, 11, 11, 10, 9, 6, 4, 3, 5, 7, 9, 11, 10, 8, 5, 4, 3, 3, 4, 5, 3, 1, 0, 0, 2, ],
    [7, 10, 12, 13, 14, 13, 12, 10, 7, 4, 2, 1, 0, 1, 2, 4, 7, 11, 13, 14, 13, 11, 7, 3, 1, 0, 1, 3, 7, 14, 7, 0, ],
    [7, 13, 11, 8, 11, 13, 9, 6, 11, 14, 12, 7, 9, 10, 6, 2, 7, 12, 8, 4, 5, 7, 2, 0, 3, 8, 5, 1, 3, 6, 3, 1, ],
    [0, 8, 15, 7, 1, 8, 14, 7, 2, 8, 13, 7, 3, 8, 12, 7, 4, 8, 11, 7, 5, 8, 10, 7, 6, 8, 9, 7, 7, 8, 8, 7, ],
    [7, 8, 6, 9, 5, 10, 4, 11, 3, 12, 2, 13, 1, 14, 0, 15, 0, 15, 1, 14, 2, 13, 3, 12, 4, 11, 5, 10, 6, 9, 7, 8, ],
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, ],
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, ],
];

fn main() {
    println!("Hello, world!");

    for (idx, w) in WAVEDATA.iter().enumerate() {

        let name = format!("wave{}.wav", idx);
        let file = File::create(name).unwrap();
        let writer = BufWriter::new(file);
        let mut wave_writer = WaveWriter::new(1, 44100, 8, writer).unwrap();

        for e in w.iter() {
            wave_writer.write_sample_u8(*e * 16 ).unwrap();
        }
        

	}

}

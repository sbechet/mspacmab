mod reverse;

use reverse::Reverse;
use std::env;

fn help() {
    println!("usage: video-offset-to-xy [0x]<offset-in-hex> -- Return (x,y) video coords");
}


fn main() -> Result<(), core::convert::Infallible> {

    let args: Vec<String> = env::args().collect();

    match args.len() {
        1 => help(),
        2 => {
            let arg_without_prefix = &args[1].trim_start_matches("0x");
            match i64::from_str_radix(arg_without_prefix, 16) {
                /* modulo 0x400 so 0x4000 and 0x4400 video offset ok */
                Ok(n) => println!("{:?}", Reverse::reverse((n % 0x400) as usize)),
                Err(_e) => help(),
            } 
        },
        _ => {
            help();
        }
    }

    Ok( () )
}

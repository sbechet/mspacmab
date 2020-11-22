extern crate video_offset_to_xy;

mod original_maze_data;

use video_offset_to_xy::reverse::Reverse;
use original_maze_data::{EASTER_EGG};
use original_maze_data::{MAZE_TABLE_1,MAZE_TABLE_2,MAZE_TABLE_3,MAZE_TABLE_4};
use original_maze_data::{PELLETS_TABLE_FOR_MAZE_1,PELLETS_TABLE_FOR_MAZE_2,PELLETS_TABLE_FOR_MAZE_3,PELLETS_TABLE_FOR_MAZE_4};
use original_maze_data::{POWER_PELLET_PER_MAP_FOR_MAZE_1,POWER_PELLET_PER_MAP_FOR_MAZE_2,POWER_PELLET_PER_MAP_FOR_MAZE_3,POWER_PELLET_PER_MAP_FOR_MAZE_4};

fn print_maze(text_maze: &[ [u8; 28]; 36 ] ) {
    println!("[");
    for y in 0..36 {
        print!("    [");
        for x in 0..28 {
            print!("0x{:02x},", text_maze[y][x]);
        }
        println!("],");
    }
    println!("];");
}

fn create_maze(maze: &[u8]) -> [ [u8; 28]; 36 ] {
    let mut text_maze: [ [u8; 28]; 36 ] = [ [0x40; 28]; 36];
    let mut maze_index = 0;
    let mut destination_index:u16 = 0;

    loop {
        let mut e = maze[maze_index];
        if e == 0 {
            break;
        }

        // data is an offset?
        if e < 0x80 {
            destination_index += e as u16 - 1;
            maze_index += 1;
            e = maze[maze_index];
        }

        destination_index += 1;

        let coord = Reverse::reverse(destination_index as usize);
        // println!("coord={:?}, value=0x{:x}, ",coord, e);

        let mirror_coord = (27 - coord.0, coord.1);
        // println!("mirror coord={:?}, mirror value=0x{:x}",mirror_coord, e^1);

        text_maze[coord.1 as usize][coord.0 as usize] = e;
        text_maze[mirror_coord.1 as usize][mirror_coord.0 as usize] = e ^ 1;

        maze_index += 1;
    }

    return text_maze;
}

fn add_pellets(pellets: &[u8]) -> Vec<(u16,u16)> {
    let mut destination_index:u16 = 0;
    let mut offset: Vec<(u16,u16)> = vec![];

    for e in pellets {
        destination_index += *e as u16;
        let coord = Reverse::reverse(destination_index as usize);
        offset.push(coord);
    }
    return offset;
}

fn maze() {
    let mut level1_text_maze = create_maze(&MAZE_TABLE_1);
    let mut level2_text_maze = create_maze(&MAZE_TABLE_2);
    let mut level3_text_maze = create_maze(&MAZE_TABLE_3);
    let mut level4_text_maze = create_maze(&MAZE_TABLE_4);


    println!("// src:88c1");
    print!("pub const MAZE_LEVEL1: [ [u8; 28]; 36] = ");
    print_maze(&level1_text_maze);
    println!("// src:8bae");
    print!("pub const MAZE_LEVEL2: [ [u8; 28]; 36] = ");
    print_maze(&level2_text_maze);
    println!("// src:8ea8");
    print!("pub const MAZE_LEVEL3: [ [u8; 28]; 36] = ");
    print_maze(&level3_text_maze);
    println!("// src:9179");
    print!("pub const MAZE_LEVEL4: [ [u8; 28]; 36] = ");
    print_maze(&level4_text_maze);
    println!("];");
    println!("// src:9474");
    println!("pub const MAZE: [ &[ [u8; 28]; 36 ]; 4] = [&MAZE_LEVEL1, &MAZE_LEVEL2, &MAZE_LEVEL3, &MAZE_LEVEL4];");


    let level1_pellets = add_pellets(&PELLETS_TABLE_FOR_MAZE_1);
    let level2_pellets = add_pellets(&PELLETS_TABLE_FOR_MAZE_2);
    let level3_pellets = add_pellets(&PELLETS_TABLE_FOR_MAZE_3);
    let level4_pellets = add_pellets(&PELLETS_TABLE_FOR_MAZE_4);

    println!("// src:8a3b");
    println!("pub const PELLET_LEVEL1: [ (u8,u8); 220] = {:?};", level1_pellets);
    println!("// src:8d27");
    println!("pub const PELLET_LEVEL2: [ (u8,u8); 240] = {:?};", level2_pellets);
    println!("// src:9018");
    println!("pub const PELLET_LEVEL3: [ (u8,u8); 238] = {:?};", level3_pellets);
    println!("// src:92ec");
    println!("pub const PELLET_LEVEL4: [ (u8,u8); 234] = {:?};", level4_pellets);
    println!("pub const PELLET: [ &[u8]; 4] = [ &PELLET_LEVEL1, &PELLET_LEVEL2, PELLET_LEVEL3, PELLET_LEVEL4 ];");

}

fn create_easter_egg() -> [ [char; 28]; 36 ] {
    let mut screen: [ [char; 28]; 36 ] = [ [' '; 28]; 36];
    let mut video_offset: usize = 0x00a2;
    let pill = '*';

    for relative_offset in EASTER_EGG.iter() {
        // println!("video_offset={:x}", video_offset);
        let coord = Reverse::reverse(video_offset);
        screen[coord.1 as usize][coord.0 as usize] = pill;
        // println!("coord={:?}, value=0x{:x}, ",coord, pill);

        video_offset += *relative_offset as usize;
    }

    println!("// src:3a4f");
    print!("pub const NAMCO_EASTER_EGG: [ [char; 28]; 36] = ");
    println!("[");
    for y in 0..36 {
        print!("    [");
        for x in 0..28 {
            print!("'{}',", screen[y][x]);
        }
        println!("],");
    }
    println!("];");

    return screen;
}

fn main() {
    println!("// Extracted using mspacmab/maze_data sub-project");
    create_easter_egg();
    println!("// Extracted using mspacmab/maze_data sub-project");
    maze();
}

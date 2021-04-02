/*
The hardware displays a 28 by 32 tile of 8x8 pixel sprites..  Every
character on the display can be using a different color set, and every
character itself is a four-color character.  Background sprites are 8x8
pixels, Floating sprites are 16x16 pixels.  Background sprites can only
be displayed in that 28x32 grid, whereas floating sprites can be anywhere
in the 224x256 display.  ( 8*28 x 8*32 ) = ( 224 x 256 )

The background sprites and the Floating sprites are stored in different
roms, so you can have completely unrelated sprites in the background
or floating over it in the foreground.  However, they both reference
the same color palettes.  Pac-Man allows for only one set of each to
be available. (One background sprite set and one floating sprite set.)
Pengo hardware allows you to switch between two sets of each. (two
background sprite sets, and two floating sprite sets).  These can be
switched between at runtime.



The Video RAM is the space in memory where you setup the background tiles
of sprites.  This is almost the same as drawing with ANSI graphics in
MS-DOS.  The Video RAM is where you would write sprites to be displayed.
For example, at coordinate (4,5) place the letter "J".


Pacman video memory map

This is the layout of the video memory (1K from 000h to 3FFh, followed by 1K of color information with an identical arrangement). 
Note that the columns 0, 1, 30 and 31 are not visible on the screen, so the actual resolution is 28x36 characters, or 224x288 pixels.

	0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16	17	18	19	20	21	22	23	24	25	26	27	28	29	30	31
0	3DF	3DE	3DD	3DC	3DB	3DA	3D9	3D8	3D7	3D6	3D5	3D4	3D3	3D2	3D1	3D0	3CF	3CE	3CD	3CC	3CB	3CA	3C9	3C8	3C7	3C6	3C5	3C4	3C3	3C2	3C1	3C0
1	3FF	3FE	3FD	3FC	3FB	3FA	3F9	3F8	3F7	3F6	3F5	3F4	3F3	3F2	3F1	3F0	3EF	3EE	3ED	3EC	3EB	3EA	3E9	3E8	3E7	3E6	3E5	3E4	3E3	3E2	3E1	3E0
2			3A0	380	360	340	320	300	2E0	2C0	2A0	280	260	240	220	200	1E0	1C0	1A0	180	160	140	120	100	0E0	0C0	0A0	080	060	040		
3			3A1	381	361	341	321	301	2E1	2C1	2A1	281	261	241	221	201	1E1	1C1	1A1	181	161	141	121	101	0E1	0C1	0A1	081	061	041		
4			3A2	382	362	342	322	302	2E2	2C2	2A2	282	262	242	222	202	1E2	1C2	1A2	182	162	142	122	102	0E2	0C2	0A2	082	062	042		
5			3A3	383	363	343	323	303	2E3	2C3	2A3	283	263	243	223	203	1E3	1C3	1A3	183	163	143	123	103	0E3	0C3	0A3	083	063	043		
6			3A4	384	364	344	324	304	2E4	2C4	2A4	284	264	244	224	204	1E4	1C4	1A4	184	164	144	124	104	0E4	0C4	0A4	084	064	044		
7			3A5	385	365	345	325	305	2E5	2C5	2A5	285	265	245	225	205	1E5	1C5	1A5	185	165	145	125	105	0E5	0C5	0A5	085	065	045		
8			3A6	386	366	346	326	306	2E6	2C6	2A6	286	266	246	226	206	1E6	1C6	1A6	186	166	146	126	106	0E6	0C6	0A6	086	066	046		
9			3A7	387	367	347	327	307	2E7	2C7	2A7	287	267	247	227	207	1E7	1C7	1A7	187	167	147	127	107	0E7	0C7	0A7	087	067	047		
10			3A8	388	368	348	328	308	2E8	2C8	2A8	288	268	248	228	208	1E8	1C8	1A8	188	168	148	128	108	0E8	0C8	0A8	088	068	048		
11			3A9	389	369	349	329	309	2E9	2C9	2A9	289	269	249	229	209	1E9	1C9	1A9	189	169	149	129	109	0E9	0C9	0A9	089	069	049		
12			3AA	38A	36A	34A	32A	30A	2EA	2CA	2AA	28A	26A	24A	22A	20A	1EA	1CA	1AA	18A	16A	14A	12A	10A	0EA	0CA	0AA	08A	06A	04A		
13			3AB	38B	36B	34B	32B	30B	2EB	2CB	2AB	28B	26B	24B	22B	20B	1EB	1CB	1AB	18B	16B	14B	12B	10B	0EB	0CB	0AB	08B	06B	04B		
14			3AC	38C	36C	34C	32C	30C	2EC	2CC	2AC	28C	26C	24C	22C	20C	1EC	1CC	1AC	18C	16C	14C	12C	10C	0EC	0CC	0AC	08C	06C	04C		
15			3AD	38D	36D	34D	32D	30D	2ED	2CD	2AD	28D	26D	24D	22D	20D	1ED	1CD	1AD	18D	16D	14D	12D	10D	0ED	0CD	0AD	08D	06D	04D		
16			3AE	38E	36E	34E	32E	30E	2EE	2CE	2AE	28E	26E	24E	22E	20E	1EE	1CE	1AE	18E	16E	14E	12E	10E	0EE	0CE	0AE	08E	06E	04E		
17			3AF	38F	36F	34F	32F	30F	2EF	2CF	2AF	28F	26F	24F	22F	20F	1EF	1CF	1AF	18F	16F	14F	12F	10F	0EF	0CF	0AF	08F	06F	04F		
18			3B0	390	370	350	330	310	2F0	2D0	2B0	290	270	250	230	210	1F0	1D0	1B0	190	170	150	130	110	0F0	0D0	0B0	090	070	050		
19			3B1	391	371	351	331	311	2F1	2D1	2B1	291	271	251	231	211	1F1	1D1	1B1	191	171	151	131	111	0F1	0D1	0B1	091	071	051		
20			3B2	392	372	352	332	312	2F2	2D2	2B2	292	272	252	232	212	1F2	1D2	1B2	192	172	152	132	112	0F2	0D2	0B2	092	072	052		
21			3B3	393	373	353	333	313	2F3	2D3	2B3	293	273	253	233	213	1F3	1D3	1B3	193	173	153	133	113	0F3	0D3	0B3	093	073	053		
22			3B4	394	374	354	334	314	2F4	2D4	2B4	294	274	254	234	214	1F4	1D4	1B4	194	174	154	134	114	0F4	0D4	0B4	094	074	054		
23			3B5	395	375	355	335	315	2F5	2D5	2B5	295	275	255	235	215	1F5	1D5	1B5	195	175	155	135	115	0F5	0D5	0B5	095	075	055		
24			3B6	396	376	356	336	316	2F6	2D6	2B6	296	276	256	236	216	1F6	1D6	1B6	196	176	156	136	116	0F6	0D6	0B6	096	076	056		
25			3B7	397	377	357	337	317	2F7	2D7	2B7	297	277	257	237	217	1F7	1D7	1B7	197	177	157	137	117	0F7	0D7	0B7	097	077	057		
26			3B8	398	378	358	338	318	2F8	2D8	2B8	298	278	258	238	218	1F8	1D8	1B8	198	178	158	138	118	0F8	0D8	0B8	098	078	058		
27			3B9	399	379	359	339	319	2F9	2D9	2B9	299	279	259	239	219	1F9	1D9	1B9	199	179	159	139	119	0F9	0D9	0B9	099	079	059		
28			3BA	39A	37A	35A	33A	31A	2FA	2DA	2BA	29A	27A	25A	23A	21A	1FA	1DA	1BA	19A	17A	15A	13A	11A	0FA	0DA	0BA	09A	07A	05A		
29			3BB	39B	37B	35B	33B	31B	2FB	2DB	2BB	29B	27B	25B	23B	21B	1FB	1DB	1BB	19B	17B	15B	13B	11B	0FB	0DB	0BB	09B	07B	05B		
30			3BC	39C	37C	35C	33C	31C	2FC	2DC	2BC	29C	27C	25C	23C	21C	1FC	1DC	1BC	19C	17C	15C	13C	11C	0FC	0DC	0BC	09C	07C	05C		
31			3BD	39D	37D	35D	33D	31D	2FD	2DD	2BD	29D	27D	25D	23D	21D	1FD	1DD	1BD	19D	17D	15D	13D	11D	0FD	0DD	0BD	09D	07D	05D		
32			3BE	39E	37E	35E	33E	31E	2FE	2DE	2BE	29E	27E	25E	23E	21E	1FE	1DE	1BE	19E	17E	15E	13E	11E	0FE	0DE	0BE	09E	07E	05E		
33			3BF	39F	37F	35F	33F	31F	2FF	2DF	2BF	29F	27F	25F	23F	21F	1FF	1DF	1BF	19F	17F	15F	13F	11F	0FF	0DF	0BF	09F	07F	05F		
34	01F	01E	01D	01C	01B	01A	019	018	017	016	015	014	013	012	011	010	00F	00E	00D	00C	00B	00A	009	008	007	006	005	004	003	002	001	000
35	03F	03E	03D	03C	03B	03A	039	038	037	036	035	034	033	032	031	030	02F	02E	02D	02C	02B	02A	029	028	027	026	025	024	023	022	021	020

*/

const REVERSE_VIDEO: [ (u16, u16); 0x400] = [
//      000      001      002      003      004      005      006      007      008      009      00A      00B      00C      00D      00E      00F      010      011      012      013      014      015      016      017      018      019      01A      01B      01C      01D      01E      01F
    (31,34), (30,34), (29,34), (28,34), (27,34), (26,34), (25,34), (24,34), (23,34), (22,34), (21,34), (20,34), (19,34), (18,34), (17,34), (16,34), (15,34), (14,34), (13,34), (12,34), (11,34), (10,34), ( 9,34), ( 8,34), ( 7,34), ( 6,34), ( 5,34), ( 4,34), ( 3,34), ( 2,34), ( 1,34), ( 0,34),
    (31,35), (30,35), (29,35), (28,35), (27,35), (26,35), (25,35), (24,35), (23,35), (22,35), (21,35), (20,35), (19,35), (18,35), (17,35), (16,35), (15,35), (14,35), (13,35), (12,35), (11,35), (10,35), ( 9,35), ( 8,35), ( 7,35), ( 6,35), ( 5,35), ( 4,35), ( 3,35), ( 2,35), ( 1,35), ( 0,35),
    (29, 2), (29, 3), (29, 4), (29, 5), (29, 6), (29, 7), (29, 8), (29, 9), (29,10), (29,11), (29,12), (29,13), (29,14), (29,15), (29,16), (29,17), (29,18), (29,19), (29,20), (29,21), (29,22), (29,23), (29,24), (29,25), (29,26), (29,27), (29,28), (29,29), (29,30), (29,31), (29,32), (29,33), 
    (28, 2), (28, 3), (28, 4), (28, 5), (28, 6), (28, 7), (28, 8), (28, 9), (28,10), (28,11), (28,12), (28,13), (28,14), (28,15), (28,16), (28,17), (28,18), (28,19), (28,20), (28,21), (28,22), (28,23), (28,24), (28,25), (28,26), (28,27), (28,28), (28,29), (28,30), (28,31), (28,32), (28,33), 
    (27, 2), (27, 3), (27, 4), (27, 5), (27, 6), (27, 7), (27, 8), (27, 9), (27,10), (27,11), (27,12), (27,13), (27,14), (27,15), (27,16), (27,17), (27,18), (27,19), (27,20), (27,21), (27,22), (27,23), (27,24), (27,25), (27,26), (27,27), (27,28), (27,29), (27,30), (27,31), (27,32), (27,33), 
    (26, 2), (26, 3), (26, 4), (26, 5), (26, 6), (26, 7), (26, 8), (26, 9), (26,10), (26,11), (26,12), (26,13), (26,14), (26,15), (26,16), (26,17), (26,18), (26,19), (26,20), (26,21), (26,22), (26,23), (26,24), (26,25), (26,26), (26,27), (26,28), (26,29), (26,30), (26,31), (26,32), (26,33), 
    (25, 2), (25, 3), (25, 4), (25, 5), (25, 6), (25, 7), (25, 8), (25, 9), (25,10), (25,11), (25,12), (25,13), (25,14), (25,15), (25,16), (25,17), (25,18), (25,19), (25,20), (25,21), (25,22), (25,23), (25,24), (25,25), (25,26), (25,27), (25,28), (25,29), (25,30), (25,31), (25,32), (25,33), 
    (24, 2), (24, 3), (24, 4), (24, 5), (24, 6), (24, 7), (24, 8), (24, 9), (24,10), (24,11), (24,12), (24,13), (24,14), (24,15), (24,16), (24,17), (24,18), (24,19), (24,20), (24,21), (24,22), (24,23), (24,24), (24,25), (24,26), (24,27), (24,28), (24,29), (24,30), (24,31), (24,32), (24,33), 
    (23, 2), (23, 3), (23, 4), (23, 5), (23, 6), (23, 7), (23, 8), (23, 9), (23,10), (23,11), (23,12), (23,13), (23,14), (23,15), (23,16), (23,17), (23,18), (23,19), (23,20), (23,21), (23,22), (23,23), (23,24), (23,25), (23,26), (23,27), (23,28), (23,29), (23,30), (23,31), (23,32), (23,33), 
    (22, 2), (22, 3), (22, 4), (22, 5), (22, 6), (22, 7), (22, 8), (22, 9), (22,10), (22,11), (22,12), (22,13), (22,14), (22,15), (22,16), (22,17), (22,18), (22,19), (22,20), (22,21), (22,22), (22,23), (22,24), (22,25), (22,26), (22,27), (22,28), (22,29), (22,30), (22,31), (22,32), (22,33), 
    (21, 2), (21, 3), (21, 4), (21, 5), (21, 6), (21, 7), (21, 8), (21, 9), (21,10), (21,11), (21,12), (21,13), (21,14), (21,15), (21,16), (21,17), (21,18), (21,19), (21,20), (21,21), (21,22), (21,23), (21,24), (21,25), (21,26), (21,27), (21,28), (21,29), (21,30), (21,31), (21,32), (21,33), 
    (20, 2), (20, 3), (20, 4), (20, 5), (20, 6), (20, 7), (20, 8), (20, 9), (20,10), (20,11), (20,12), (20,13), (20,14), (20,15), (20,16), (20,17), (20,18), (20,19), (20,20), (20,21), (20,22), (20,23), (20,24), (20,25), (20,26), (20,27), (20,28), (20,29), (20,30), (20,31), (20,32), (20,33), 
    (19, 2), (19, 3), (19, 4), (19, 5), (19, 6), (19, 7), (19, 8), (19, 9), (19,10), (19,11), (19,12), (19,13), (19,14), (19,15), (19,16), (19,17), (19,18), (19,19), (19,20), (19,21), (19,22), (19,23), (19,24), (19,25), (19,26), (19,27), (19,28), (19,29), (19,30), (19,31), (19,32), (19,33), 
    (18, 2), (18, 3), (18, 4), (18, 5), (18, 6), (18, 7), (18, 8), (18, 9), (18,10), (18,11), (18,12), (18,13), (18,14), (18,15), (18,16), (18,17), (18,18), (18,19), (18,20), (18,21), (18,22), (18,23), (18,24), (18,25), (18,26), (18,27), (18,28), (18,29), (18,30), (18,31), (18,32), (18,33), 
    (17, 2), (17, 3), (17, 4), (17, 5), (17, 6), (17, 7), (17, 8), (17, 9), (17,10), (17,11), (17,12), (17,13), (17,14), (17,15), (17,16), (17,17), (17,18), (17,19), (17,20), (17,21), (17,22), (17,23), (17,24), (17,25), (17,26), (17,27), (17,28), (17,29), (17,30), (17,31), (17,32), (17,33), 
    (16, 2), (16, 3), (16, 4), (16, 5), (16, 6), (16, 7), (16, 8), (16, 9), (16,10), (16,11), (16,12), (16,13), (16,14), (16,15), (16,16), (16,17), (16,18), (16,19), (16,20), (16,21), (16,22), (16,23), (16,24), (16,25), (16,26), (16,27), (16,28), (16,29), (16,30), (16,31), (16,32), (16,33), 
    (15, 2), (15, 3), (15, 4), (15, 5), (15, 6), (15, 7), (15, 8), (15, 9), (15,10), (15,11), (15,12), (15,13), (15,14), (15,15), (15,16), (15,17), (15,18), (15,19), (15,20), (15,21), (15,22), (15,23), (15,24), (15,25), (15,26), (15,27), (15,28), (15,29), (15,30), (15,31), (15,32), (15,33), 
    (14, 2), (14, 3), (14, 4), (14, 5), (14, 6), (14, 7), (14, 8), (14, 9), (14,10), (14,11), (14,12), (14,13), (14,14), (14,15), (14,16), (14,17), (14,18), (14,19), (14,20), (14,21), (14,22), (14,23), (14,24), (14,25), (14,26), (14,27), (14,28), (14,29), (14,30), (14,31), (14,32), (14,33), 
    (13, 2), (13, 3), (13, 4), (13, 5), (13, 6), (13, 7), (13, 8), (13, 9), (13,10), (13,11), (13,12), (13,13), (13,14), (13,15), (13,16), (13,17), (13,18), (13,19), (13,20), (13,21), (13,22), (13,23), (13,24), (13,25), (13,26), (13,27), (13,28), (13,29), (13,30), (13,31), (13,32), (13,33), 
    (12, 2), (12, 3), (12, 4), (12, 5), (12, 6), (12, 7), (12, 8), (12, 9), (12,10), (12,11), (12,12), (12,13), (12,14), (12,15), (12,16), (12,17), (12,18), (12,19), (12,20), (12,21), (12,22), (12,23), (12,24), (12,25), (12,26), (12,27), (12,28), (12,29), (12,30), (12,31), (12,32), (12,33), 
    (11, 2), (11, 3), (11, 4), (11, 5), (11, 6), (11, 7), (11, 8), (11, 9), (11,10), (11,11), (11,12), (11,13), (11,14), (11,15), (11,16), (11,17), (11,18), (11,19), (11,20), (11,21), (11,22), (11,23), (11,24), (11,25), (11,26), (11,27), (11,28), (11,29), (11,30), (11,31), (11,32), (11,33), 
    (10, 2), (10, 3), (10, 4), (10, 5), (10, 6), (10, 7), (10, 8), (10, 9), (10,10), (10,11), (10,12), (10,13), (10,14), (10,15), (10,16), (10,17), (10,18), (10,19), (10,20), (10,21), (10,22), (10,23), (10,24), (10,25), (10,26), (10,27), (10,28), (10,29), (10,30), (10,31), (10,32), (10,33), 
    ( 9, 2), ( 9, 3), ( 9, 4), ( 9, 5), ( 9, 6), ( 9, 7), ( 9, 8), ( 9, 9), ( 9,10), ( 9,11), ( 9,12), ( 9,13), ( 9,14), ( 9,15), ( 9,16), ( 9,17), ( 9,18), ( 9,19), ( 9,20), ( 9,21), ( 9,22), ( 9,23), ( 9,24), ( 9,25), ( 9,26), ( 9,27), ( 9,28), ( 9,29), ( 9,30), ( 9,31), ( 9,32), ( 9,33), 
    ( 8, 2), ( 8, 3), ( 8, 4), ( 8, 5), ( 8, 6), ( 8, 7), ( 8, 8), ( 8, 9), ( 8,10), ( 8,11), ( 8,12), ( 8,13), ( 8,14), ( 8,15), ( 8,16), ( 8,17), ( 8,18), ( 8,19), ( 8,20), ( 8,21), ( 8,22), ( 8,23), ( 8,24), ( 8,25), ( 8,26), ( 8,27), ( 8,28), ( 8,29), ( 8,30), ( 8,31), ( 8,32), ( 8,33), 
    ( 7, 2), ( 7, 3), ( 7, 4), ( 7, 5), ( 7, 6), ( 7, 7), ( 7, 8), ( 7, 9), ( 7,10), ( 7,11), ( 7,12), ( 7,13), ( 7,14), ( 7,15), ( 7,16), ( 7,17), ( 7,18), ( 7,19), ( 7,20), ( 7,21), ( 7,22), ( 7,23), ( 7,24), ( 7,25), ( 7,26), ( 7,27), ( 7,28), ( 7,29), ( 7,30), ( 7,31), ( 7,32), ( 7,33), 
    ( 6, 2), ( 6, 3), ( 6, 4), ( 6, 5), ( 6, 6), ( 6, 7), ( 6, 8), ( 6, 9), ( 6,10), ( 6,11), ( 6,12), ( 6,13), ( 6,14), ( 6,15), ( 6,16), ( 6,17), ( 6,18), ( 6,19), ( 6,20), ( 6,21), ( 6,22), ( 6,23), ( 6,24), ( 6,25), ( 6,26), ( 6,27), ( 6,28), ( 6,29), ( 6,30), ( 6,31), ( 6,32), ( 6,33), 
    ( 5, 2), ( 5, 3), ( 5, 4), ( 5, 5), ( 5, 6), ( 5, 7), ( 5, 8), ( 5, 9), ( 5,10), ( 5,11), ( 5,12), ( 5,13), ( 5,14), ( 5,15), ( 5,16), ( 5,17), ( 5,18), ( 5,19), ( 5,20), ( 5,21), ( 5,22), ( 5,23), ( 5,24), ( 5,25), ( 5,26), ( 5,27), ( 5,28), ( 5,29), ( 5,30), ( 5,31), ( 5,32), ( 5,33), 
    ( 4, 2), ( 4, 3), ( 4, 4), ( 4, 5), ( 4, 6), ( 4, 7), ( 4, 8), ( 4, 9), ( 4,10), ( 4,11), ( 4,12), ( 4,13), ( 4,14), ( 4,15), ( 4,16), ( 4,17), ( 4,18), ( 4,19), ( 4,20), ( 4,21), ( 4,22), ( 4,23), ( 4,24), ( 4,25), ( 4,26), ( 4,27), ( 4,28), ( 4,29), ( 4,30), ( 4,31), ( 4,32), ( 4,33), 
    ( 3, 2), ( 3, 3), ( 3, 4), ( 3, 5), ( 3, 6), ( 3, 7), ( 3, 8), ( 3, 9), ( 3,10), ( 3,11), ( 3,12), ( 3,13), ( 3,14), ( 3,15), ( 3,16), ( 3,17), ( 3,18), ( 3,19), ( 3,20), ( 3,21), ( 3,22), ( 3,23), ( 3,24), ( 3,25), ( 3,26), ( 3,27), ( 3,28), ( 3,29), ( 3,30), ( 3,31), ( 3,32), ( 3,33), 
    ( 2, 2), ( 2, 3), ( 2, 4), ( 2, 5), ( 2, 6), ( 2, 7), ( 2, 8), ( 2, 9), ( 2,10), ( 2,11), ( 2,12), ( 2,13), ( 2,14), ( 2,15), ( 2,16), ( 2,17), ( 2,18), ( 2,19), ( 2,20), ( 2,21), ( 2,22), ( 2,23), ( 2,24), ( 2,25), ( 2,26), ( 2,27), ( 2,28), ( 2,29), ( 2,30), ( 2,31), ( 2,32), ( 2,33), 
    (31, 0), (30, 0), (29, 0), (28, 0), (27, 0), (26, 0), (25, 0), (24, 0), (23, 0), (22, 0), (21, 0), (20, 0), (19, 0), (18, 0), (17, 0), (16, 0), (15, 0), (14, 0), (13, 0), (12, 0), (11, 0), (10, 0), ( 9, 0), ( 8, 0), ( 7, 0), ( 6, 0), ( 5, 0), ( 4, 0), ( 3, 0), ( 2, 0), ( 1, 0), ( 0, 0),
    (31, 1), (30, 1), (29, 1), (28, 1), (27, 1), (26, 1), (25, 1), (24, 1), (23, 1), (22, 1), (21, 1), (20, 1), (19, 1), (18, 1), (17, 1), (16, 1), (15, 1), (14, 1), (13, 1), (12, 1), (11, 1), (10, 1), ( 9, 1), ( 8, 1), ( 7, 1), ( 6, 1), ( 5, 1), ( 4, 1), ( 3, 1), ( 2, 1), ( 1, 1), ( 0, 1),
];

pub struct Reverse;

impl Reverse {
    pub fn reverse(offset: usize) -> (u16, u16) {
        let mut r = REVERSE_VIDEO[offset];

        /* Convert to _real_ screen position, ignore invisible coords */
        if  r.0 ==  0 ||
            r.0 ==  1 ||
            r.0 == 30 ||
            r.0 == 31 {
                /* to reveal invisible coords */
                r.0 = 65535 - r.0;
                r.1 = 65535 - r.1;
        }

        r.0 -= 2;

        if r.1 == 0 || r.1 == 1 || r.1 == 34 || r.1 == 35 {
            r.0 -= 2;
        }

        r
    }
}


#include "stage.h"

#include "mem.h"
#include "audio.h"
#include "pad.h"
#include "main.h"
#include "random.h"

#include "object/combo.h"

//Stage constants
#define INPUT_LEFT  (PAD_LEFT  | PAD_SQUARE)
#define INPUT_DOWN  (PAD_DOWN  | PAD_CROSS)
#define INPUT_UP    (PAD_UP    | PAD_TRIANGLE)
#define INPUT_RIGHT (PAD_RIGHT | PAD_CIRCLE)

//Stage definitions
static const StageDef stage_defs[StageId_Max] = {
	{ //StageId_1_1 (Bopeebo)
		//Characters
		{CharId_BF,   FIXED_DEC(120,1),  FIXED_DEC(100,1)},
		{CharId_Dad, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		
		//Song info
		{FIXED_DEC(1,1),FIXED_DEC(1,1),FIXED_DEC(13,10)},
		1, 1,
		XA_Bopeebo, 0,
	},
	{ //StageId_1_2 (Fresh)
		//Characters
		{CharId_BF,   FIXED_DEC(120,1),  FIXED_DEC(100,1)},
		{CharId_Dad, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		
		//Song info
		{FIXED_DEC(1,1),FIXED_DEC(13,10),FIXED_DEC(18,10)},
		1, 2,
		XA_Fresh, 2,
	},
	{ //StageId_1_3 (Dadbattle)
		//Characters
		{CharId_BF,   FIXED_DEC(120,1),  FIXED_DEC(100,1)},
		{CharId_Dad, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		
		//Song info
		{FIXED_DEC(13,10),FIXED_DEC(15,10),FIXED_DEC(23,10)},
		1, 3,
		XA_Dadbattle, 0,
	},
	{ //StageId_1_4 (Tutorial)
		//Characters
		{CharId_BF,  FIXED_DEC(120,1),  FIXED_DEC(100,1)},
		{CharId_Dad,   FIXED_DEC(0,1),    FIXED_DEC(0,1)},
		
		//Song info
		{FIXED_DEC(1,1),FIXED_DEC(1,1),FIXED_DEC(1,1)},
		1, 4,
		XA_Tutorial, 2,
	},
	
	{ //StageId_2_1 (Spookeez)
		//Characters
		{CharId_BF,   FIXED_DEC(120,1),  FIXED_DEC(100,1)},
		{CharId_Dad, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		
		//Song info
		{FIXED_DEC(1,1),FIXED_DEC(17,10),FIXED_DEC(24,10)},
		2, 1,
		XA_Spookeez, 0,
	},
	{ //StageId_2_2 (South)
		//Characters
		{CharId_BF,   FIXED_DEC(120,1),  FIXED_DEC(100,1)},
		{CharId_Dad, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		
		//Song info
		{FIXED_DEC(11,10),FIXED_DEC(15,10),FIXED_DEC(22,10)},
		2, 2,
		XA_South, 2,
	},
	{ //StageId_2_3 (Monster)
		//Characters
		{CharId_BF,   FIXED_DEC(120,1),  FIXED_DEC(100,1)},
		{CharId_Dad, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		
		//Song info
		{FIXED_DEC(13,10),FIXED_DEC(13,10),FIXED_DEC(16,10)},
		2, 3,
		XA_Monster, 0,
	},
	
	{ //StageId_3_1 (Pico)
		//Characters
		{CharId_BF,   FIXED_DEC(120,1),  FIXED_DEC(100,1)},
		{CharId_Dad, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		
		//Song info
		{FIXED_DEC(12,10),FIXED_DEC(14,10),FIXED_DEC(16,10)},
		3, 1,
		XA_Pico, 0,
	},
	{ //StageId_3_2 (Philly)
		//Characters
		{CharId_BF,   FIXED_DEC(120,1),  FIXED_DEC(100,1)},
		{CharId_Dad, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		
		//Song info
		{FIXED_DEC(1,1),FIXED_DEC(13,10),FIXED_DEC(2,1)},
		3, 2,
		XA_Philly, 2,
	},
	{ //StageId_3_3 (Blammed)
		//Characters
		{CharId_BF,   FIXED_DEC(120,1),  FIXED_DEC(100,1)},
		{CharId_Dad, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		
		//Song info
		{FIXED_DEC(12,10),FIXED_DEC(15,10),FIXED_DEC(23,10)},
		3, 3,
		XA_Blammed, 0,
	},
	
	{ //StageId_4_1 (Satin Panties)
		//Characters
		{CharId_BF,   FIXED_DEC(120,1),  FIXED_DEC(100,1)},
		{CharId_Dad, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		
		//Song info
		{FIXED_DEC(13,10),FIXED_DEC(16,10),FIXED_DEC(18,10)},
		4, 1,
		XA_SatinPanties, 0,
	},
	{ //StageId_4_2 (High)
		//Characters
		{CharId_BF,   FIXED_DEC(120,1),  FIXED_DEC(100,1)},
		{CharId_Dad, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		
		//Song info
		{FIXED_DEC(13,10),FIXED_DEC(18,10),FIXED_DEC(2,1)},
		4, 2,
		XA_High, 2,
	},
	{ //StageId_4_3 (MILF)
		//Characters
		{CharId_BF,   FIXED_DEC(120,1),  FIXED_DEC(100,1)},
		{CharId_Dad, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		
		//Song info
		{FIXED_DEC(14,10),FIXED_DEC(17,10),FIXED_DEC(26,10)},
		4, 3,
		XA_MILF, 0,
	},
	{ //StageId_4_4 (Test)
		//Characters
		{CharId_BF,   FIXED_DEC(120,1),  FIXED_DEC(100,1)},
		{CharId_Dad, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		
		//Song info
		{FIXED_DEC(16,10),FIXED_DEC(16,10),FIXED_DEC(16,10)},
		4, 4,
		XA_Test, 2,
	},
};

//Stage state
Stage stage;

//Stage music functions
void Stage_StartVocal()
{
	if (!stage.vocal_active)
	{
		Audio_ChannelXA(stage.stage_def->music_channel);
		stage.vocal_active = true;
	}
}

void Stage_CutVocal()
{
	if (stage.vocal_active)
	{
		Audio_ChannelXA(stage.stage_def->music_channel + 1);
		stage.vocal_active = false;
	}
}

//Stage camera functions
void Stage_FocusCharacter(Character *ch, fixed_t div)
{
	//Use character focus settings to update target position and zoom
	stage.camera.tx = ch->x * 2 / 3;
	stage.camera.ty = ch->y / 3 - ch->focus_height;
	stage.camera.tz = ch->focus_zoom;
	stage.camera.td = div;
}

void Stage_ScrollCamera()
{
	//Get delta position
	fixed_t dx = stage.camera.tx - stage.camera.x;
	fixed_t dy = stage.camera.ty - stage.camera.y;
	fixed_t dz = stage.camera.tz - stage.camera.zoom;
	
	//Scroll based off current divisor
	stage.camera.x += FIXED_MUL(dx, stage.camera.td);
	stage.camera.y += FIXED_MUL(dy, stage.camera.td);
	stage.camera.zoom += FIXED_MUL(dz, stage.camera.td);
}

//Stage section functions
void Stage_ChangeBPM(u16 bpm, u16 step)
{
	//Update last BPM
	stage.last_bpm = bpm;
	
	//Update timing base
	if (stage.step_crochet)
		stage.time_base += FIXED_DIV(((fixed_t)step - stage.step_base) << FIXED_SHIFT, stage.step_crochet);
	stage.step_base = step;
	
	//Get new crochet
	fixed_t bpm_dec = ((fixed_t)bpm << FIXED_SHIFT) / 24;
	stage.step_crochet = FIXED_DIV(bpm_dec, FIXED_DEC(15,1));
	
	//Get new crochet based values
	stage.note_speed = FIXED_MUL(FIXED_DIV(FIXED_DEC(140,1), stage.step_crochet), stage.speed);
	
	stage.late_safe = stage.step_crochet / 6; //10 frames
	stage.early_safe = stage.late_safe >> 1;
}

Section *Stage_GetPrevSection(Section *section)
{
	if (section > stage.sections)
		return section - 1;
	return NULL;
}

u16 Stage_GetSectionLength(Section *section)
{
	Section *prev = Stage_GetPrevSection(section);
	if (prev == NULL)
		return section->end;
	return section->end - prev->end;
}

u16 Stage_GetSectionStart(Section *section)
{
	Section *prev = Stage_GetPrevSection(section);
	if (prev == NULL)
		return 0;
	return prev->end;
}

//Section scroll structure
typedef struct
{
	fixed_t start;   //Seconds
	fixed_t length;  //Seconds
	u16 start_step;  //Sub-steps
	u16 length_step; //Sub-steps
} SectionScroll;

void Stage_GetSectionScroll(SectionScroll *scroll, Section *section)
{
	//Get BPM
	u16 bpm = section->flag & SECTION_FLAG_BPM_MASK;
	fixed_t bpm_dec = ((fixed_t)bpm << FIXED_SHIFT) / 24;
	
	//Get section step info
	scroll->start_step = Stage_GetSectionStart(section) * 24;
	scroll->length_step = (section->end * 24) - scroll->start_step;
	
	//Get section time length            15/24
	scroll->length = FIXED_DIV(FIXED_DEC(625,1000) * scroll->length_step, bpm_dec);
}

//Note hit detection
static const CharAnim note_anims[4][2] = {
	{CharAnim_Left,  CharAnim_LeftAlt},
	{CharAnim_Down,  CharAnim_DownAlt},
	{CharAnim_Up,    CharAnim_UpAlt},
	{CharAnim_Right, CharAnim_RightAlt},
};

void Stage_HitNote(fixed_t offset)
{
	//Get hit type
	if (offset < 0)
		offset = -offset;
	
	u8 hit_type;
	if (offset > stage.late_safe * 9 / 10)
		hit_type = 3; //SHIT
	else if (offset > stage.late_safe * 3 / 4)
		hit_type = 2; //BAD
	else if (offset > stage.late_safe / 5)
		hit_type = 1; //GOOD
	else
		hit_type = 0; //SICK
	
	//Increment combo
	stage.combo++;
	
	//Create combo object telling of our combo
	Obj_Combo *combo = Obj_Combo_New(
		stage.player->x,
		stage.player->y - stage.player->focus_height,
		hit_type,
		stage.combo >= 10 ? stage.combo : 0xFFFF
	);
	if (combo != NULL)
		ObjectList_Add(&stage.objlist_fg, (Object*)combo);
}

void Stage_MissNote(u8 type)
{
	if (stage.combo)
	{
		//Kill combo
		stage.combo = 0;
		
		//Create combo object telling of our lost combo
		Obj_Combo *combo = Obj_Combo_New(
			stage.player->x,
			stage.player->y - stage.player->focus_height,
			0xFF,
			0
		);
		if (combo != NULL)
			ObjectList_Add(&stage.objlist_fg, (Object*)combo);
	}
}

void Stage_NoteCheck(u8 type)
{
	//Perform note check
	for (Note *note = stage.cur_note;; note++)
	{
		//Check if note can be hit
		fixed_t note_fp = ((fixed_t)note->pos << FIXED_SHIFT) / 24;
		if (note_fp - stage.early_safe > stage.note_scroll)
			break;
		if (note_fp + stage.late_safe < stage.note_scroll)
			continue;
		if ((note->type & NOTE_FLAG_HIT) || (note->type & (NOTE_FLAG_OPPONENT | 0x3)) != type || (note->type & NOTE_FLAG_SUSTAIN))
			continue;
		
		//Hit the note
		note->type |= NOTE_FLAG_HIT;
		
		stage.player->set_anim(stage.player, note_anims[type][0]);
		Stage_HitNote(stage.note_scroll - note_fp);
		
		Stage_StartVocal();
		stage.health += 230;
		stage.arrow_hitan[type] = 6;
		return;
	}
	
	//Missed a note
	stage.player->set_anim(stage.player, note_anims[type][1]);
	Stage_MissNote(type);
	
	stage.health -= 400;
}

void Stage_SustainCheck(u8 type)
{
	//Hold note animation
	if (stage.arrow_hitan[type] == 0)
		stage.arrow_hitan[type] = 1;
	
	//Perform note check
	boolean near_note = false;
	
	for (Note *note = stage.cur_note;; note++)
	{
		//Check if note can be hit
		fixed_t note_fp = ((fixed_t)note->pos << FIXED_SHIFT) / 24;
		if (note_fp - stage.early_safe > stage.note_scroll)
			break;
		if (note_fp + stage.late_safe < stage.note_scroll)
			continue;
		if ((note->type & (NOTE_FLAG_OPPONENT | 0x3)) != type)
			continue;
		near_note = true;
		if ((note->type & NOTE_FLAG_HIT) || !(note->type & NOTE_FLAG_SUSTAIN))
			continue;
		
		//Hit the note
		note->type |= NOTE_FLAG_HIT;
		
		if (stage.player->animatable.anim != note_anims[type][0])
			stage.player->set_anim(stage.player, note_anims[type][0]);
		
		Stage_StartVocal();
		stage.health += 230;
		stage.arrow_hitan[type] = 6;
		return;
	}
	
	//Hold animation
	if ((stage.just_step || !near_note) && stage.player->animatable.anim == note_anims[type][0])
		stage.player->set_anim(stage.player, note_anims[type][0]);
}

//Stage drawing functions
void Stage_DrawTex(Gfx_Tex *tex, RECT *src, RECT_FIXED *dst, fixed_t zoom)
{
	fixed_t l = (SCREEN_WIDTH2  << FIXED_SHIFT) + FIXED_MUL(dst->x, zoom);
	fixed_t t = (SCREEN_HEIGHT2 << FIXED_SHIFT) + FIXED_MUL(dst->y, zoom);
	fixed_t r = l + FIXED_MUL(dst->w, zoom);
	fixed_t b = t + FIXED_MUL(dst->h, zoom);
	
	l >>= FIXED_SHIFT;
	t >>= FIXED_SHIFT;
	r >>= FIXED_SHIFT;
	b >>= FIXED_SHIFT;
	
	RECT sdst = {
		l,
		t,
		r - l,
		b - t,
	};
	Gfx_DrawTex(tex, src, &sdst);
}

//Stage HUD functions and constants
static const fixed_t note_x[8] = {
	//BF
	 FIXED_DEC(26,1),
	 FIXED_DEC(60,1),//+34
	 FIXED_DEC(94,1),
	FIXED_DEC(128,1),
	//Opponent
	FIXED_DEC(-128,1),
	 FIXED_DEC(-94,1),//+34
	 FIXED_DEC(-60,1),
	 FIXED_DEC(-26,1),
};
static const fixed_t note_y = (32 - SCREEN_HEIGHT2) << FIXED_SHIFT;

void Stage_DrawHealth(u8 i, s8 ox)
{
	//Check if we should use 'dying' frame
	s8 dying;
	if (ox < 0)
		dying = (stage.health >= 18000) * 24;
	else
		dying = (stage.health <= 2000) * 24;
	
	//Get src and dst
	fixed_t hx = (128 << FIXED_SHIFT) * (10000 - stage.health) / 10000;
	RECT src = {
		(i % 5) * 48 + dying,
		16 + (i / 5) * 24,
		24,
		24
	};
	RECT_FIXED dst = {
		hx + ox * FIXED_DEC(11,1) - FIXED_DEC(12,1),
		(SCREEN_HEIGHT2 - 32 + 4 - 12) << FIXED_SHIFT,
		src.w << FIXED_SHIFT,
		src.h << FIXED_SHIFT
	};
	
	//Draw health icon
	Stage_DrawTex(&stage.tex_hud1, &src, &dst, FIXED_MUL(stage.bump, stage.sbump));
}

void Stage_DrawNotes()
{
	//Initialize scroll state
	SectionScroll scroll;
	scroll.start = stage.time_base;
	
	Section *scroll_section = stage.section_base;
	Stage_GetSectionScroll(&scroll, scroll_section);
	
	//Push scroll back until cur_note is properly contained
	while (scroll.start_step > stage.cur_note->pos)
	{
		//Look for previous section
		Section *prev_section = Stage_GetPrevSection(scroll_section);
		if (prev_section == NULL)
			break;
		
		//Push scroll back
		scroll_section = prev_section;
		Stage_GetSectionScroll(&scroll, scroll_section);
		scroll.start -= scroll.length;
	}
	
	//Draw notes
	for (Note *note = stage.cur_note;; note++)
	{
		//Update scroll
		while (note->pos >= scroll_section->end * 24)
		{
			//Push scroll forward
			scroll.start += scroll.length;
			Stage_GetSectionScroll(&scroll, ++scroll_section);
		}
		
		//Get note time
		fixed_t time = (scroll.start - stage.song_time) + (scroll.length * (note->pos - scroll.start_step) / scroll.length_step);
		fixed_t y = note_y + FIXED_MUL(stage.speed, time * 140);
		
		//Check if went above screen
		if (y < ((-16 - SCREEN_HEIGHT2) << FIXED_SHIFT))
		{
			//Miss note if player's note
			if (!(note->type & (NOTE_FLAG_OPPONENT | NOTE_FLAG_HIT)))
			{
				//Missed note
				Stage_CutVocal();
				Stage_MissNote(note->type & 0x3);
				stage.health -= 475;
			}
			
			//Update current note
			stage.cur_note++;
		}
		else
		{
			//Don't draw if below screen
			if (y > ((SCREEN_HEIGHT2 + 16) << FIXED_SHIFT) || note->pos == 0xFFFF)
				break;
			
			//Draw note
			if (note->type & NOTE_FLAG_SUSTAIN)
			{
				//Check for sustain clipping
				fixed_t clip;
				if (note->type & (NOTE_FLAG_HIT | NOTE_FLAG_OPPONENT))
				{
					clip = (((32 + 16) - SCREEN_HEIGHT2) << FIXED_SHIFT) - y;
					if (clip < 0)
						clip = 0;
				}
				else
				{
					clip = 0;
				}
				
				//Draw sustain
				if (note->type & NOTE_FLAG_SUSTAIN_END)
				{
					if (clip < (24 << FIXED_SHIFT))
					{
						RECT note_src = {
							160,
							((note->type & 0x3) << 5) + 8 + (clip >> FIXED_SHIFT),
							32,
							24 - (clip >> FIXED_SHIFT)
						};
						RECT_FIXED note_dst = {
							note_x[note->type & 0x7] - FIXED_DEC(16,1),
							y - FIXED_DEC(12,1) + clip,
							note_src.w << FIXED_SHIFT,
							(note_src.h << FIXED_SHIFT)
						};
						Stage_DrawTex(&stage.tex_hud0, &note_src, &note_dst, stage.bump);
					}
				}
				else
				{
					if (clip < stage.note_speed)
					{
						RECT note_src = {
							160,
							((note->type & 0x3) << 5),
							32,
							16
						};
						RECT_FIXED note_dst = {
							note_x[note->type & 0x7] - FIXED_DEC(16,1),
							y - FIXED_DEC(12,1) + clip,
							note_src.w << FIXED_SHIFT,
							stage.note_speed - clip
						};
						Stage_DrawTex(&stage.tex_hud0, &note_src, &note_dst, stage.bump);
					}
				}
			}
			else
			{
				//Draw note
				if (note->type & NOTE_FLAG_HIT)
					continue;
				
				RECT note_src = {32 + ((note->type & 0x3) << 5), 0, 32, 32};
				RECT_FIXED note_dst = {
					note_x[note->type & 0x7] - FIXED_DEC(16,1),
					y - FIXED_DEC(16,1),
					note_src.w << FIXED_SHIFT,
					note_src.h << FIXED_SHIFT
				};
				Stage_DrawTex(&stage.tex_hud0, &note_src, &note_dst, stage.bump);
			}
		}
	}
}

//Stage functions
void Stage_Load(StageId id, StageDiff difficulty)
{
	//Get stage definition
	const StageDef *stage_def = stage.stage_def = &stage_defs[stage.stage_id = id];
	
	//Load HUD textures
	Gfx_LoadTex(&stage.tex_hud0, IO_Read("\\STAGE\\HUD0.TIM;1"), GFX_LOADTEX_FREE);
	Gfx_LoadTex(&stage.tex_hud1, IO_Read("\\STAGE\\HUD1.TIM;1"), GFX_LOADTEX_FREE);
	Gfx_LoadTex(&stage.tex_back0, IO_Read("\\WEEK1\\BACK0.TIM;1"), GFX_LOADTEX_FREE);
	Gfx_LoadTex(&stage.tex_back1, IO_Read("\\WEEK1\\BACK1.TIM;1"), GFX_LOADTEX_FREE);
	
	//Load characters
	stage.player = Character_New(stage_def->pchar.id, stage_def->pchar.x, stage_def->pchar.y);
	stage.opponent = Character_New(stage_def->ochar.id, stage_def->ochar.x, stage_def->ochar.y);
	
	//Load stage data
	char chart_path[64];
	sprintf(chart_path, "\\WEEK%d\\%d.%d%c.CHT;1", stage_def->week, stage_def->week, stage_def->week_song, "ENH"[difficulty]);
	
	stage.chart_data = IO_Read(chart_path);
	stage.sections = (Section*)((u8*)stage.chart_data + 2);
	stage.notes = (Note*)((u8*)stage.chart_data + *((u16*)stage.chart_data));
	
	stage.cur_section = stage.sections;
	stage.cur_note = stage.notes;
	
	stage.speed = stage_def->speed[difficulty];
	
	stage.step_crochet = 0;
	stage.time_base = 0;
	stage.step_base = 0;
	stage.section_base = stage.cur_section;
	Stage_ChangeBPM(stage.cur_section->flag & SECTION_FLAG_BPM_MASK, 0);
	
	//Initialize stage state
	stage.note_scroll = FIXED_DEC(-8,1);
	
	stage.just_step = false;
	
	memset(stage.arrow_hitan, 0, sizeof(stage.arrow_hitan));
	
	stage.health = 10000;
	stage.score = 0;
	stage.combo = 0;
	
	stage.state = StageState_Play;
	
	stage.objlist_fg = NULL;
	stage.objlist_bg = NULL;
	
	//Initialize camera
	if (stage.cur_section->flag & SECTION_FLAG_OPPFOCUS)
		Stage_FocusCharacter(stage.opponent, FIXED_UNIT / 24);
	else
		Stage_FocusCharacter(stage.player, FIXED_UNIT / 24);
	stage.camera.x = stage.camera.tx;
	stage.camera.y = stage.camera.ty;
	stage.camera.zoom = stage.camera.tz;
	
	Gfx_SetClear(62, 48, 64);
	
	//Find music file and initialize music state
	Audio_GetXAFile(&stage.music_file, stage_def->music_track);
	IO_SeekFile(&stage.music_file);
	stage.vocal_active = false;
}

void Stage_Unload()
{
	//Unload stage data
	Mem_Free(stage.chart_data);
	
	//Free objects
	ObjectList_Free(&stage.objlist_fg);
	ObjectList_Free(&stage.objlist_bg);
	
	//Free characters
	Character_Free(stage.player);
	Character_Free(stage.opponent);
}

void Stage_Tick()
{
	switch (stage.state)
	{
		case StageState_Play:
		{
			//Get song position
			boolean playing;
			
			if (stage.note_scroll < 0)
			{
				//Song hasn't started yet
				fixed_t next_scroll = stage.note_scroll + stage.step_crochet / 60; //TODO: PAL
				
				//3 2 1 GO - pre song start
				
				//Update song
				if (next_scroll >= 0)
				{
					//Song has started
					playing = true;
					Audio_PlayXA_File(&stage.music_file, 0x40, stage.stage_def->music_channel, 0);
					stage.note_scroll = 0;
					stage.song_time = 0;
					stage.just_step = true;
				}
				else
				{
					//Still scrolling
					playing = false;
					if ((stage.note_scroll & FIXED_UAND) != (next_scroll & FIXED_UAND))
						stage.just_step = true;
					else
						stage.just_step = false;
					stage.note_scroll = next_scroll;
					
					//Extrapolate song time from note scroll
					stage.song_time = FIXED_DIV(stage.note_scroll, stage.step_crochet);
				}
			}
			else if (Audio_PlayingXA())
			{
				//Get playing song position
				fixed_t song_time = (Audio_TellXA_Milli() << FIXED_SHIFT) / 1000;
				playing = true;
				
				//Update scroll
				fixed_t next_scroll = ((fixed_t)stage.step_base << FIXED_SHIFT) + FIXED_MUL(song_time - stage.time_base, stage.step_crochet);
				
				if (next_scroll > stage.note_scroll) //Skipping?
				{
					if ((stage.note_scroll & FIXED_UAND) != (next_scroll & FIXED_UAND))
						stage.just_step = true;
					else
						stage.just_step = false;
					stage.note_scroll = next_scroll;
					stage.song_time = song_time;
				}
			}
			else
			{
				//Song has ended
				fixed_t next_scroll = stage.note_scroll + stage.step_crochet / 60; //TODO: PAL
				playing = false;
				
				//Update scroll
				if ((stage.note_scroll & FIXED_UAND) != (next_scroll & FIXED_UAND))
					stage.just_step = true;
				else
					stage.just_step = false;
				stage.note_scroll = next_scroll;
				
				//Extrapolate song time from note scroll
				stage.song_time = stage.time_base + FIXED_DIV(stage.note_scroll - ((fixed_t)stage.step_base << FIXED_SHIFT), stage.step_crochet);
			}
			
			//Get song step
			stage.song_step = stage.note_scroll >> FIXED_SHIFT;
			
			//Update section
			while (stage.note_scroll >= 0)
			{
				//Check if current section has ended
				if (stage.song_step < stage.cur_section->end)
					break;
				
				//Update BPM
				Stage_ChangeBPM(stage.cur_section[1].flag & SECTION_FLAG_BPM_MASK, stage.cur_section->end);
				stage.section_base = stage.cur_section + 1;
				
				//Start next section
				stage.cur_section++;
				if (stage.cur_section->flag & SECTION_FLAG_OPPFOCUS)
					Stage_FocusCharacter(stage.opponent, FIXED_UNIT / 24);
				else
					Stage_FocusCharacter(stage.player, FIXED_UNIT / 24);
			}
			
			//Get bump
			if (playing)
			{
				//Bump every 16 steps
				if ((stage.song_step & 0xF) == 0)
					stage.bump = (fixed_t)FIXED_UNIT + ((fixed_t)(FIXED_DEC(75,100) - (stage.note_scroll & FIXED_LAND)) / 16);
				else
					stage.bump = FIXED_UNIT;
				
				//Bump every 4 steps
				if ((stage.song_step & 0x3) == 0)
					stage.sbump = (fixed_t)FIXED_UNIT + ((fixed_t)(FIXED_DEC(75,100) - (stage.note_scroll & FIXED_LAND)) / 24);
				else
					stage.sbump = FIXED_UNIT;
			}
			else
			{
				//Song isn't playing yet
				stage.bump = FIXED_UNIT;
				stage.sbump = FIXED_UNIT;
			}
			
			//Scroll camera
			Stage_ScrollCamera();
			
			//Handle player note presses
			if (playing)
			{
				if (pad_state.press & INPUT_LEFT)
					Stage_NoteCheck(0);
				if (pad_state.press & INPUT_DOWN)
					Stage_NoteCheck(1);
				if (pad_state.press & INPUT_UP)
					Stage_NoteCheck(2);
				if (pad_state.press & INPUT_RIGHT)
					Stage_NoteCheck(3);
				
				if (pad_state.held & INPUT_LEFT)
					Stage_SustainCheck(0);
				if (pad_state.held & INPUT_DOWN)
					Stage_SustainCheck(1);
				if (pad_state.held & INPUT_UP)
					Stage_SustainCheck(2);
				if (pad_state.held & INPUT_RIGHT)
					Stage_SustainCheck(3);
			}
			
			//Process notes
			for (Note *note = stage.cur_note;; note++)
			{
				if (note->pos > ((stage.note_scroll * 24) >> FIXED_SHIFT))
					break;
				
				//Opponent note hits
				if (playing && (note->type & NOTE_FLAG_OPPONENT) && !(note->type & NOTE_FLAG_HIT))
				{
					//Opponent hits note
					Stage_StartVocal();
					stage.opponent->set_anim(stage.opponent, note_anims[note->type & 0x3][(stage.cur_section->flag & SECTION_FLAG_ALTANIM) != 0]);
					note->type |= NOTE_FLAG_HIT;
				}
			}
			
			//Perform health checks
			if (stage.health <= 0)
			{
				//Player has died
				stage.health = 0;
				stage.state = StageState_Dead;
			}
			if (stage.health > 20000)
				stage.health = 20000;
			
			//Draw health heads
			Stage_DrawHealth(stage.player->health_i,    1);
			Stage_DrawHealth(stage.opponent->health_i, -1);
			
			//Draw health bar
			RECT health_fill = {0, 0, 256 - (256 * stage.health / 20000), 8};
			RECT health_back = {0, 8, 256, 8};
			RECT_FIXED health_dst = {FIXED_DEC(-128,1), (SCREEN_HEIGHT2 - 32) << FIXED_SHIFT, 0, FIXED_DEC(8,1)};
			
			health_dst.w = health_fill.w << FIXED_SHIFT;
			Stage_DrawTex(&stage.tex_hud1, &health_fill, &health_dst, stage.bump);
			health_dst.w = health_back.w << FIXED_SHIFT;
			Stage_DrawTex(&stage.tex_hud1, &health_back, &health_dst, stage.bump);
			
			//Draw stage notes
			Stage_DrawNotes();
			
			//Draw note HUD
			RECT note_src = {0, 0, 32, 32};
			RECT_FIXED note_dst = {0, note_y - FIXED_DEC(16,1), FIXED_DEC(32,1), FIXED_DEC(32,1)};
			
			for (u8 i = 0; i < 4; i++)
			{
				//BF
				note_dst.x = note_x[i] - FIXED_DEC(16,1);
				
				if (stage.arrow_hitan[i] != 0)
				{
					//Play hit animation
					note_src.x = (i + 1) << 5;
					note_src.y = 128 - (((stage.arrow_hitan[i] + 1) >> 1) << 5);
					stage.arrow_hitan[i]--;
				}
				else
				{
					note_src.x = 0;
					note_src.y = i << 5;
				}
				Stage_DrawTex(&stage.tex_hud0, &note_src, &note_dst, stage.bump);
				
				//Opponent
				note_dst.x = note_x[i | 0x4] - FIXED_DEC(16,1);
				
				note_src.x = 0;
				note_src.y = i << 5;
				Stage_DrawTex(&stage.tex_hud0, &note_src, &note_dst, stage.bump);
			}
			
			//Tick foreground objects
			ObjectList_Tick(&stage.objlist_fg);
			
			//Tick characters
			stage.player->tick(stage.player);
			stage.opponent->tick(stage.opponent);
			
			//Tick background objects
			ObjectList_Tick(&stage.objlist_bg);
			
			//Draw curtains
			RECT curtain_src = {0, 0, 128, 256};
			RECT_FIXED curtain1_dst = {
				FIXED_DEC(-300,1) - stage.camera.x,
				FIXED_DEC(-350,1) - stage.camera.y,
				FIXED_DEC(200,1),
				FIXED_DEC(400,1)
			};
			RECT_FIXED curtainr_dst = {
				FIXED_DEC(300,1) - stage.camera.x,
				FIXED_DEC(-350,1) - stage.camera.y,
				FIXED_DEC(-200,1),
				FIXED_DEC(400,1)
			};
			
			Stage_DrawTex(&stage.tex_back1, &curtain_src, &curtain1_dst, FIXED_MUL(FIXED_DEC(95,100), stage.bump));
			Stage_DrawTex(&stage.tex_back1, &curtain_src, &curtainr_dst, FIXED_MUL(FIXED_DEC(95,100), stage.bump));
			
			//Draw stage
			RECT stagel_src = {0, 0, 256, 128};
			RECT_FIXED stage1_dst = {
				FIXED_DEC(-500,1) - stage.camera.x,
				FIXED_DEC(32,1) - stage.camera.y,
				FIXED_DEC(500,1),
				FIXED_DEC(250,1)
			};
			RECT stager_src = {0, 128, 256, 128};
			RECT_FIXED stager_dst = {
				-stage.camera.x,
				FIXED_DEC(32,1) - stage.camera.y,
				FIXED_DEC(500,1),
				FIXED_DEC(250,1)
			};
			
			Stage_DrawTex(&stage.tex_back0, &stagel_src, &stage1_dst, stage.bump);
			Stage_DrawTex(&stage.tex_back0, &stager_src, &stager_dst, stage.bump);
			break;
		}
		case StageState_Dead: //Start BREAK animation and reading extra data from CD
		{
			//Stop music immediately
			Audio_StopXA();
			
			//Unload stage data
			Mem_Free(stage.chart_data);
			stage.chart_data = NULL;
			
			//Free objects
			ObjectList_Free(&stage.objlist_fg);
			ObjectList_Free(&stage.objlist_bg);
			
			//Free opponent
			Character_Free(stage.opponent);
			stage.opponent = NULL;
			
			//Reset stage state
			stage.just_step = false;
			stage.bump = stage.sbump = FIXED_UNIT;
			
			//Change background colour to black
			Gfx_SetClear(0, 0, 0);
			
			//Knock camera about
			stage.camera.x += RandomRange(FIXED_DEC(-8,1), FIXED_DEC(8,1));
			stage.camera.y += RandomRange(FIXED_DEC(-8,1), FIXED_DEC(8,1));
			
			//Run death animation, focus on player, and change state
			stage.player->set_anim(stage.player, PlayerAnim_Dead0);
			
			stage.camera.tx = stage.player->x;
			stage.camera.ty = stage.player->y - stage.player->focus_height;
			stage.camera.tz = stage.player->focus_zoom;
			stage.camera.td = FIXED_UNIT / 40;
			
			stage.state = StageState_DeadLoad;
		}
	//Fallthrough
		case StageState_DeadLoad:
		{
			//Scroll camera and tick player
			Stage_ScrollCamera();
			stage.player->tick(stage.player);
			
			//Drop mic and change state if CD has finished reading and animation has ended
			if (IO_IsReading() || stage.player->animatable.anim != PlayerAnim_Dead1)
				break;
			
			stage.player->set_anim(stage.player, PlayerAnim_Dead2);
			stage.state = StageState_DeadDrop;
			break;
		}
		case StageState_DeadDrop:
		{
			//Scroll camera and tick player
			Stage_ScrollCamera();
			stage.player->tick(stage.player);
			
			//Enter next state once mic has been dropped
			if (stage.player->animatable.anim == PlayerAnim_Dead3)
			{
				stage.state = StageState_DeadRetry;
				Audio_PlayXA_Track(XA_GameOver, 0x40, 1, true);
			}
			break;
		}
		case StageState_DeadRetry:
		{
			//Randomly twitch
			if (stage.player->animatable.anim == PlayerAnim_Dead3)
			{
				if (RandomRange(0, 29) == 0)
					stage.player->set_anim(stage.player, PlayerAnim_Dead4);
				if (RandomRange(0, 29) == 0)
					stage.player->set_anim(stage.player, PlayerAnim_Dead5);
			}
			
			//Scroll camera and tick player
			Stage_ScrollCamera();
			stage.player->tick(stage.player);
			break;
		}
		default:
			break;
	}
}

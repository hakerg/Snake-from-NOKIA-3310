#include "Change_Tempo.h"
#include "Scene_Manager.h"
#include "Data_Container.h"



Change_Tempo::Change_Tempo() :
	Menu({ 2, 1 }, { "100 BPM", "110 BPM", "120 BPM", "130 BPM", "140 BPM", "150 BPM", "160 BPM", "170 BPM", "180 BPM", "190 BPM", "200 BPM", "210 BPM", "220 BPM", "230 BPM", "240 BPM" })
{
}


Change_Tempo::~Change_Tempo()
{
}


void Change_Tempo::item_selected(int id)
{
	switch (id)
	{
	case 0: data.song.bpm = 100; break;
	case 1: data.song.bpm = 110; break;
	case 2: data.song.bpm = 120; break;
	case 3: data.song.bpm = 130; break;
	case 4: data.song.bpm = 140; break;
	case 5: data.song.bpm = 150; break;
	case 6: data.song.bpm = 160; break;
	case 7: data.song.bpm = 170; break;
	case 8: data.song.bpm = 180; break;
	case 9: data.song.bpm = 190; break;
	case 10: data.song.bpm = 200; break;
	case 11: data.song.bpm = 210; break;
	case 12: data.song.bpm = 220; break;
	case 13: data.song.bpm = 230; break;
	case 14: data.song.bpm = 240; break;
	}
	Scene_Manager::go_to_previous_scene();
	Scene_Manager::go_to_previous_scene();
}
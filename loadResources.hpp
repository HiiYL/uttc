#ifndef LOADRESOURCES_HPP_INCLUDED
#define LOADRESOURCES_HPP_INCLUDED
#include "helper.hpp"
void loadResources (ResourceHolder* resources)  {
    resources->textures.load("LocalBase", "resources/images/local_base.png");
    resources->textures.load("LocalHover", "resources/images/local_hover.png");
    resources->textures.load("NetworkBase", "resources/images/network_base.png");
    resources->textures.load("NetworkHover", "resources/images/network_hover.png");
    resources->textures.load("ViewReplaysBase", "resources/images/view_replays_base.png");
    resources->textures.load("ViewReplaysHover", "resources/images/view_replays_hover.png");

    resources->textures.load("MouseCursor", "resources/images/cursorHand_grey.png");
    resources->textures.load("MockCursor", "resources/images/cursorHand_beige.png");
    resources->textures.load("ExitButton", "resources/images/quit.png");
    resources->textures.load("GameBackground","resources/images/background.png");
    resources->textures.load("Background", "resources/images/background.png");
    resources->textures.load("BackgroundClouds", "resources/images/background6.png");
    resources->textures.load("Home", "resources/images/home.png");
    resources->textures.load("Player1Mark", "resources/images/cross.png");
    resources->textures.load("Player2Mark", "resources/images/circle.png");

    resources->textures.load("Settings", "resources/images/settings.png");


    resources->textures.load("MusicMuteBase", "resources/images/music_mute_base.png");
    resources->textures.load("MusicPlayBase", "resources/images/music_play_base.png");
    resources->textures.load("MusicMuteHover", "resources/images/music_mute_hover.png");
    resources->textures.load("MusicPlayHover", "resources/images/music_play_hover.png");
    resources->textures.load("TimerBase", "resources/images/timer_base.png");
    resources->textures.load("TimerHover", "resources/images/timer_hover.png");
    resources->textures.load("MenuBase", "resources/images/menu_base.png");
    resources->textures.load("MenuHover", "resources/images/menu_hover.png");

    resources->textures.load("Overlay","resources/images/box.png");

    resources->textures.load("PlayAgain","resources/images/replay.png");
    resources->textures.load("Exit", "resources/images/quit.png");
    resources->textures.load("Menu", "resources/images/home.png");


    resources->textures.load("HostBase","resources/images/host_base.png");
    resources->textures.load("JoinBase", "resources/images/join_base.png");
    resources->textures.load("HostHover","resources/images/host_hover.png");
    resources->textures.load("JoinHover","resources/images/join_hover.png");


    resources->textures.load("AddressBarBase", "resources/images/address_bar_base.png");
    resources->textures.load("AddressBarHover", "resources/images/address_bar_hover.png");

    resources->textures.load("ChatBase", "resources/images/chat_base.png");
    resources->textures.load("ChatHover", "resources/images/chat_hover.png");
    resources->textures.load("ChatBox", "resources/images/chatbox.png");

    resources->textures.load("BackBase", "resources/images/back_base.png");
    resources->textures.load("BackHover", "resources/images/back_hover.png");

    resources->textures.load("ResumeBase", "resources/images/resume_base.png");
    resources->textures.load("ResumeHover", "resources/images/resume_hover.png");


    resources->textures.load("ReturnMainMenuBase","resources/images/return_main_menu_base.png");
    resources->textures.load("ReturnMainMenuHover","resources/images/return_main_menu_hover.png");
    resources->textures.load("RestartBase", "resources/images/restart_base.png");
    resources->textures.load("RestartHover", "resources/images/restart_hover.png");
    resources->textures.load("ExitBase", "resources/images/exit_base.png");
    resources->textures.load("ExitHover", "resources/images/exit_hover.png");

    resources->textures.load("MatchReplayBase", "resources/images/match_replay_base.png");
    resources->textures.load("MatchReplayHover", "resources/images/match_replay_hover.png");
    resources->textures.load("TimerIncrease", "resources/images/increase_arrow.png");
    resources->textures.load("TimerDecrease", "resources/images/decrease_arrow.png");
    resources->textures.load("ActivateTimerBase", "resources/images/timer_activate_base.png");
    resources->textures.load("ActivateTimerHover", "resources/images/timer_activate_hover.png");
    resources->textures.load("DeactivateTimerBase", "resources/images/timer_deactivate_base.png");
    resources->textures.load("DeactivateTimerHover", "resources/images/timer_deactivate_hover.png");
    resources->textures.load("EditBase", "resources/images/edit_base.png");
    resources->textures.load("EditHover", "resources/images/edit_hover.png");
    resources->textures.load("TimerEditBase", "resources/images/timer_edit_base.png");
    resources->textures.load("TimerEditHover", "resources/images/timer_edit_hover.png");

    resources->textures.load("NetworkLobbyBase", "resources/images/network_lobby_base.png");
    resources->textures.load("NetworkLobbyHover", "resources/images/network_lobby_hover.png");
    resources->textures.load("WaitingBase", "resources/images/waiting_base.png");
    resources->textures.load("WaitingHover", "resources/images/waiting_hover.png");

    resources->textures.load("CircleRegBlueBase", "resources/images/circle_regular_base.png");
    resources->textures.load("CircleRegBlueHover", "resources/images/circle_regular_hover.png");
    resources->textures.load("BarGreyBase", "resources/images/bar_grey_base.png");
    resources->textures.load("BarGreyHover", "resources/images/bar_grey_hover.png");

    resources->textures.load("SaveReplayBase", "resources/images/save_replay_base.png");
    resources->textures.load("SaveReplayHover", "resources/images/save_replay_hover.png");
    resources->textures.load("Highlight", "resources/images/highlight_grid_blue.png");

    resources->sounds.load("Placement1", "resources/sounds/placement_1.ogg");
    resources->sounds.load("Placement2", "resources/sounds/placement_2.ogg");
    resources->sounds.load("PlacementInvalid1","resources/sounds/placement_invalid.ogg");
    resources->sounds.load("PlacementInvalid2","resources/sounds/placement_invalid_2.ogg");
    resources->sounds.load("Victory", "resources/sounds/victory.ogg");
    resources->sounds.load("Defeat", "resources/sounds/defeat.ogg");
    resources->sounds.load("Tie", "resources/sounds/tie.ogg");
    resources->sounds.load("MessageReceive","resources/sounds/message_receive.ogg");

    resources->fonts.load("KenVectorFuture", "resources/fonts/kenvector_future.ttf");
    resources->fonts.load("KenVecFuture", "resources/fonts/kenvector_future.ttf");
    resources->fonts.load("Simplifica", "resources/fonts/simplifica.ttf");
    resources->fonts.load("KenVecFutureThin", "resources/fonts/kenvector_future_thin.ttf");      //for sidebar
}


#endif // LOADRESOURCES_HPP_INCLUDED

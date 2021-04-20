# PS4-Notify
A different way of calling the notify function on the ps4 for homebrew development.

![alt text](https://i.imgur.com/W2Zpz33.png)

### Calling the new Notify
``` C++
void Notify(char* IconURI, char* MessageFMT, ...);
```

You can call the notify function like this using one of the default ps4 icons.

``` C++
Notify("cxml://psnotification/tex_default_icon_notification", "Hello World");
```

You dont have to use one of the default ps4 icons though using a web url will work aswell.

``` C++
Notify("http://www.somewhere.com/SomeImage.png", "Hello World"); 
```

### Some Icon URIs I have dumped
There is probably more than these but these I have tested and confirmed they do work.
```
cxml://psnotification/tex_icon_system                 //Playstation buttons
cxml://psnotification/tex_icon_ban                    //Circle with a slash
cxml://psnotification/tex_default_icon_notification   //i in a chat bubble
cxml://psnotification/tex_default_icon_message
cxml://psnotification/tex_default_icon_friend
cxml://psnotification/tex_default_icon_trophy
cxml://psnotification/tex_default_icon_download
cxml://psnotification/tex_default_icon_upload_16_9
cxml://psnotification/tex_default_icon_cloud_client   //ps now logo
cxml://psnotification/tex_default_icon_activity
cxml://psnotification/tex_default_icon_smaps          //bullhorn
cxml://psnotification/tex_default_icon_shareplay
cxml://psnotification/tex_default_icon_tips
cxml://psnotification/tex_default_icon_events
cxml://psnotification/tex_default_icon_share_screen
cxml://psnotification/tex_default_icon_community
cxml://psnotification/tex_default_icon_lfps
cxml://psnotification/tex_default_icon_tournament
cxml://psnotification/tex_default_icon_team
cxml://psnotification/tex_default_avatar
cxml://psnotification/tex_icon_capture
cxml://psnotification/tex_icon_start_rec
cxml://psnotification/tex_icon_stop_rec
cxml://psnotification/tex_icon_live_prohibited
cxml://psnotification/tex_icon_live_start
cxml://psnotification/tex_icon_loading
cxml://psnotification/tex_icon_loading_16_9
cxml://psnotification/tex_icon_countdown
cxml://psnotification/tex_icon_party
cxml://psnotification/tex_icon_shareplay
cxml://psnotification/tex_icon_broadcast
cxml://psnotification/tex_icon_psnow_toast
cxml://psnotification/tex_audio_device_headphone
cxml://psnotification/tex_audio_device_headset
cxml://psnotification/tex_audio_device_mic
cxml://psnotification/tex_audio_device_morpheus
cxml://psnotification/tex_device_battery_0
cxml://psnotification/tex_device_battery_1
cxml://psnotification/tex_device_battery_2
cxml://psnotification/tex_device_battery_3
cxml://psnotification/tex_device_battery_nocharge
cxml://psnotification/tex_device_comp_app
cxml://psnotification/tex_device_controller
cxml://psnotification/tex_device_jedi_usb
cxml://psnotification/tex_device_blaster
cxml://psnotification/tex_device_headphone
cxml://psnotification/tex_device_headset
cxml://psnotification/tex_device_keyboard
cxml://psnotification/tex_device_mic
cxml://psnotification/tex_device_morpheus
cxml://psnotification/tex_device_mouse
cxml://psnotification/tex_device_move               //ps move controller
cxml://psnotification/tex_device_remote
cxml://psnotification/tex_device_omit
cxml://psnotification/tex_icon_connect              //Weird blury thing
cxml://psnotification/tex_icon_event_toast          //Calendar
cxml://psnotification/tex_morpheus_trophy_bronze
cxml://psnotification/tex_morpheus_trophy_silver
cxml://psnotification/tex_morpheus_trophy_gold
cxml://psnotification/tex_morpheus_trophy_platinum
cxml://psnotification/tex_icon_champions_league     //The OG foot ball lol
```

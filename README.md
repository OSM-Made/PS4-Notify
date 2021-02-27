# PS4-Notify
A different way of calling the notify function on the ps4 for homebrew development.

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
cxml://psnotification/tex_icon_system               //Playstation buttons
cxml://psnotification/tex_icon_ban                  //Circle with a slash
cxml://psnotification/tex_default_icon_notification //i in a chat bubble
cxml://psnotification/tex_device_headphone
cxml://psnotification/tex_device_headset
cxml://psnotification/tex_device_mic
cxml://psnotification/tex_device_move               //ps move controller
cxml://psnotification/tex_device_mouse
cxml://psnotification/tex_device_keyboard
cxml://psnotification/tex_default_icon_message
cxml://psnotification/tex_default_icon_trophy
cxml://psnotification/tex_default_icon_friend
cxml://psnotification/tex_default_icon_download
cxml://psnotification/tex_default_icon_cloud_client //ps now logo
cxml://psnotification/tex_default_icon_smaps        //bullhorn
cxml://psnotification/tex_default_icon_activity
cxml://psnotification/tex_icon_capture
cxml://psnotification/tex_icon_stop_rec
cxml://psnotification/tex_icon_start_rec
cxml://psnotification/tex_icon_loading
cxml://psnotification/tex_icon_live_prohibited
cxml://psnotification/tex_icon_live_start
cxml://psnotification/tex_icon_party
```

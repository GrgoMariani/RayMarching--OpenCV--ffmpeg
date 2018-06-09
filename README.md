# RayMarching->OpenCV->ffmpeg

#### Description

I guess there could have been a lot of better time uses than emulating GLSL shaders in OpenCV and then pipe-ing it to ffmpeg.

There's a lot to be done here as well, such as threading.
- - - -
- - - -
## HOW TO

* ##### Step0: Prerequisites
> Make sure to install ___OpenCV___ (preferably the latest one) and install ___ffmpeg___.

* ##### Step1: Compile

>```
>g++ main.cpp -std=c++11 -o `pkg-config opencv --cflags --libs` raymarching
>```
or use
```
make
```
* ##### Step2: Use
>```
>./raymarching | ffmpeg -f rawvideo -pixel_format bgr24 -video_size 320x240 -re -framerate 10  -i - -f mpegts -preset fast -vcodec libx264 udp://localhost:5000
>```
> Pipe the output directly to ffmpeg with this command

* ##### Step3: Watch
>Open VLC player and use CTRL+N
>```
>udp://@:5000
>```


- - - -
- - - -

## Code Explanation
##### Follow xdPixel's Tutorial

Check [xdPixel's tutorial]( http://xdpixel.com/ray-marching-101-part-2/ ) for code. It's his RayMarching code after all.

## Why use this code ???
Why not ???


# RayMarching->OpenCV->ffmpeg

#### Description

I guess there could have been a lot of better time uses than emulating GLSL shaders in OpenCV and then pipe-ing it to ffmpeg.

There's a lot to be done here as well, such as threading.

### Compile

```
g++ main.cpp -std=c++11 -o `pkg-config opencv --cflags --libs` raymarching
```

### Use
```
./raymarching | ffmpeg -f rawvideo -pixel_format bgr24 -video_size 320x240 -re -framerate 10  -i - -f mpegts -preset fast -vcodec libx264 udp://localhost:5000
```
Basically it pipes the output directly to ffmpeg

### Watch
Open VLC player and use CTRL+N
```
udp://@:5000
```

### Follow xdPixel's Tutorial

Check this link ( http://xdpixel.com/ray-marching-101-part-2/ ) for code. It's his RayMarching code after all.

### Why ???
Why not ???
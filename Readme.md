# Abstract:

- Quick launch:
	not yet ready for easy use
- Download:
	`git clone https://github.com/guyver2/RayTracer.git`



# Introduction:

My modest attempt at ray tracing. 
- Current features include :
	* Discrete and area light sources
	* Monte-Carlo ray sampling
	* Difuse shadows
	* Mirrors
	



# Installation:

- Requirements:
	* OpenCV, Eigen
	* `git clone https://github.com/guyver2/RayTracer.git`

# Credits & Licence:

- Code:
	Antoine Letouzey -- [antoine.letouzey@gmail.com](antoine.letouzey@gmail.com)
- Licence:
	LGPL
- json.h:
	Copyright (c) 2013-2016 Niels Lohmann -- [https://github.com/nlohmann/json](https://github.com/nlohmann/json)

# Reference image:
First, not my result but the reference image I'm targeting

![Ref](http://www.graphics.cornell.edu/online/box/box.jpg)

# Results so far:

Color image with monte carlo sampling, spherical objects and reflections (ball and back wall).

![Rendering](https://antoine.sxbn.org/pages/projects/ray/color_bounce_mirror.jpg)

Color image with monte carlo sampling and spherical objects.

![Rendering](https://antoine.sxbn.org/pages/projects/ray/color_bounce_ball.jpg)

Color image with monte carlo sampling for ray bouncing and area light.

![Rendering](https://antoine.sxbn.org/pages/projects/ray/color_bounce_montecarlo.jpg)


Color image with ray bouncing once in 100 random directions

![Rendering](https://antoine.sxbn.org/pages/projects/ray/color_bounce.jpg)


Color image with single ray and light atenuation

![Rendering](https://antoine.sxbn.org/pages/projects/ray/current.jpg)


Depth map

![Depth](https://antoine.sxbn.org/pages/projects/ray/depth.jpg)

# Freak show:
Every rendering project is subject to some amazing failures, here is my modest contribution.

![error](https://antoine.sxbn.org/pages/projects/ray/freak_show/01_color_side_error.png)

![error](https://antoine.sxbn.org/pages/projects/ray/freak_show/03_color_error1.png)

![error](https://antoine.sxbn.org/pages/projects/ray/freak_show/3lights.png)

![error](https://antoine.sxbn.org/pages/projects/ray/freak_show/right_blast.png)

![error](https://antoine.sxbn.org/pages/projects/ray/freak_show/mirrorseverywhere.jpg)

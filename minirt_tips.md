# miniRT tips

This is a list with tips, what I wish I had when I started miniRT. It isn't a great tutorial but maybe it has a few useful links/tips. Don't forget to ask your peers!

If your math isn't great, writing a small raytracer is going to be hard but a lot of fun. Take your time. It's going to be overwhelming in the beginning, but you'll get there. Take a deep breath. Believe me, at some point it starts to make sense(most of it, anyways). One of my favorite projects.

Have fun, -jobvan-d

## great general resources:
- [Scratchapixel.com](https://www.scratchapixel.com/)  
- [Ray tracing in a weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)


## basics:
Make sure you at least know some basic linear algebra, you can learn that at [khanacademy.org](https://www.khanacademy.org) for free.
ALSO maybe watch daniels masterclass(not online yet, but slides are [here](https://github.com/GroteGnoom/codam_presentation/blob/main/vizualizing_math.pdf))
the dot product, very useful and used a lot. Make sure you also have a grasp of cosine:
- https://www.mathsisfun.com/algebra/vectors-dot-product.html
- https://www.mathsisfun.com/algebra/vectors-cross-product.html

As for the vectors, do yourself a favor, and use [vector extentions](https://gcc.gnu.org/onlinedocs/gcc/Vector-Extensions.html). This will save A LOT of time.

Also: *don't forget to normalize your vectors* (ray direction, normals, orientation, etc.). Forgetting this can cause a lot of weird bugs, and miniRT is a headache to debug.

## sphere interesection:
We didn't bother doing it with the quadratic formula, rather we did an geometric approach, at the time it was less overwhelming, even though you have to use it later on.
Here the code with explanations:
https://www.khanacademy.org/computer-programming/c/5311392656179200


## plane intersect:
Just go to [wikipedia](https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection) and try to derrive it yourself using this. It shouldn't be too hard once you did the sphere.


## lights:
idk, some scratchapixel article. Basically, on intersect, you draw a ray to every light. If there's something (an intersection) in between, it's in the shadow. Else, it's in light.
That's all. Make sure _not_ to check beyond the distance to the light(we had this bug which was took more than a week to fix), and to start a little bit off the surface, otherwise the light might intersect with the originating object itself.
useful: http://www.cs.cornell.edu/courses/cs4620/2011fa/lectures/08raytracingWeb.pdf

As for colors, I recommend using a float/double RGB vector, with `(0.0, 0.0, 0.0)` being black and `(1.0, 1.0, 1.0)` being white.

## cylinder:
https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html

This one is hard because you have to use the quadratic formula, but worse, you also have to rotate the cylinder. Rotating is hard.
We ended up using rodriguez rotation(cuz matrices 2hard4me). An outstanding tutorial on this is here: https://youtu.be/OKr0YCj0BW4

Instead of rotating the cylinder, we rotate the ray, which is defacto the same thing.
We get the angle between the default orientation(i.e. 0,1,0) and the actual orientation.
Simply do a cross product(the right hand rule) with these vectors and you've got the axis. (DON'T FORGET TO NORMALIZE!)
Now just rotate the ray(both position and direction ofcourse), et voila.

As for the caps, they're just planes with a radius.

#### Special thanks:
mjoosten, abba, dnoom, sde-rijk, jkoers, lde-la-h

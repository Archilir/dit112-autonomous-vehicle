# Filip's Fantabulous OpenCV Notes
## Images
The foundation of using CV is manipulating images. Since every frame of a video is just an image, it makes sense to learn how to manipulate them first. Retreiving an image in this manner is shown in my videoFeedExample.py snipped. Most things in OpenCV are Array or Tuple objects, and images are no exception. An image is just a 2d array of pixel objects. Pixels themselves are just an array of 3 items, representing their BGR(Blue, Red, Green) value. A pixel can be retrieved like this:

    pixel = image[x, y]
And the output for a solid blue pixel would be:

    [255, 0, 0]
To be more specific, one could also access a specific BGR value from a pixel by adding a third argument. This can be either 0 ,1 or 2 for Blue, Green or Red respectively. So for instance, this would print the blue value of the above pixel:

    >>print(image[x, y, 0])
    255
And as with any array element, we could always change it's value by passing a different BGR array:

    >>image[x, y] = [0, 255, 0]
    >>print(image[x, y, 0])
    0
Interesting thing to note - the third number is treated as a 3rd coordinate of the array, even though it just accesses the coordinate of the pixel object in that position.
### Region selection
But selecting individual pixels is not that useful. Most operations where you directly manipulate the image will be done over regions. A region is a rectangular area of an image defined by the top left and bottom right corner. It is retrieved like this:

    region = img[xx:xy, yx:yy]
where xx and xy are the coordinates of the top left corner and yx and yy are the coordinates of the bottom right corner.
Similarly, you can replace a region of an image with your own predetermined region. You do the exact opposite thing:

    img[xx:xy, yx:yy] = region

Some more auxilliary methods:

**img.shape** - returns a tuple of the image's X size, Y size and number of channels(for reference, BGR has 3 channels)
**img.size** - just like a 2d array, simply returns the number of pixel objects




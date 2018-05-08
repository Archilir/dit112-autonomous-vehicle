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
**cv2.add** - two images can be added, but this will just perform literal addition - their BGR values will be added and cap out at 255.
**cv2.addWeighted(img1, a, img2, b, c)** - weighted add is a more useful method. Rather than add pixels until a cap, it attempts to create a transparent overlay of an image over another. It uses this using an (img = a*img1 + b*img2 + c) formula, where a and b are numbers between 0 and 1. Their purpose is to determine which image should be more visible. c is a number that I don't know what it does so I just use the one provided in the example in my OpenCV python tutorial.

## Masks
Creating a mask is the first step towards object detection. A mask basically only detects parts of a frame of a certain color, such as a road sign. This part of the documentation is easiest to follow by reading along with the maskingExample snippet.

First, we must create a copy of the current frame that's in the HSV color space. As opposed to **B**lue **G**reen **R**ed, we use **H**ue **S**aturation **T**ransparency for masking. I assume this is because it's easier to get a range of color from it, because that's what we will be doing.

We convert a frame into HSV using the cv2.cvtColor method. To it, we pass the image to be converted and the conversion method we are using. In this case it's COLOR_BGR2HSV. As we see, one can specify other color spaces we want to convert between. The specific code example is: 

    hsv = cv2.cvtColor(image, COLOR_BGR2HSV)
Next, we must create a range of colors we want to use. In my example, I'm using a flat green. There is a rather simple step by step procedure we can use to retreive a range of colors for our mask.

 1. Start with a BGR color we want to mask. In our case, it's a flat green - 0, 255, 0.
 2. We will convert this color to HSV using the same cvtColor method. In this case: 
`bgr = numpy.uint8([[[0, 255, 0]]])`
`hsv = cv2.cvtColor(rgb, cv2.COLOR_BGR2HSV)`
 **Note:** singular colors use NumPy's method for creating arrays of unsigned ints because they are faster, because OpenCV uses them, and because f**k our lives.
 Printing this will return `[[[60, 255, 255]]]`
 
 3. From here, we know our H value is 60. That's all we really need to create a simple range of green colors.
 `upper = numpy.array([H+10, 255, 255])`
 `lower = numpy.array([H-10, 100, 100])`
 **Note:** I don't know why the hell we use a normal NumPy array instead of an uint8 one here. I assume it's because the next method uses that data type. All I know is that I've tested them and they aren't interchangeable.
 
 4. Now that we have our range, we can finally create our mask. Here, we use the cv2.inRange method:
`mask = cv2.inRange(hsv, lower_red, upper_red)`

From here, you can just use the normal cv2.imshow method to show the masked images. The example snippet shows how to display the normal feed, masked feed and a masked feed in color together.

## Thresholding
Thresholding is the act of taking a grayscale image , picking a color value X in it, and showing all values greater/smaller than it as black/white.
There are 5 types of normal thresholding - Binary, Binary Inverted, Truncated, ToZero and ToZero inverted. An example is seen [here](http://opencv-python-tutroals.readthedocs.io/en/latest/_images/threshold.jpg)
Creating a thresholded image is a matter of using a singular method. The only quirky part is having to assign it to not just an image variable, but a tuple of the image and something called a retval. I don't quite understand the use of it, but it hasn't interfered with my code, so it can be ignored for now. Here is a snippet from the example code:
`ret,thresh1 = cv2.threshold(image,x,y,cv2.THRESH_BINARY)`
After declaring the retval and the thresholded image, the threshold method is ran. Its arguments are:
 1. The original, grayscale image
 2. A color value - All pixels greater than this value will be turned into the Y value.
 3. Value to turn all >X pixels into
 4. Thresholding type
A more refined method to use is Adaptive thresholding, but it's impossible to use this with the Raspberry Pi camera. The reason is that Adaptive Thresholding requires a camera that can record a native grayscale feed rather than using a converted one. Shame, since adaptive thresholding seems to be much more accurate.
A solution I've played with is being able to switch color spaces of every indivitual frame to grayscale and then run adaptive thresholding on it, but I feel this will affect performance too much.



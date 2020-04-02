function [resultImage] = hide_Image(hiderImage, hiddenImage)
    resultImage = hiderImage;
    //Red
    hiderRed = hiderImage(:,:,1);
    hiddenRed = hiddenImage(:,:,1);
    resultImage(:,:,1) = hide_couche_rgb (hiderRed, hiddenRed);
    //Green
    hiderGreen = hiderImage(:,:,2);
    hiddenGreen = hiddenImage(:,:,2);
    resultImage(:,:,2) = hide_couche_rgb (hiderGreen, hiddenGreen);
    //Blue
    hiderBlue = hiderImage(:,:,3);
    hiddenBlue = hiddenImage(:,:,3);
    resultImage(:,:,3) = hide_couche_rgb (hiderBlue, hiddenBlue);
endfunction

function [resultRGB] = hide_couche_rgb(hiderRGB, hiddenRGB)
    dimension = size(hiderRGB);
    result    = double (zeros(dimension));
    hiderRGB  = double (hiderRGB);
    hiddenRGB = double (hiddenRGB);
    result    = floor (hiderRGB/16)*16+floor (hiddenRGB/16);
    resultRGB = uint8 (result);
endfunction

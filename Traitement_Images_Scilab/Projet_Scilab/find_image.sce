function [resultImage1, resultImage2] = find_Image(image)
    resultImage1 = image;
    resultImage2 = image;
    //Red
    [resultImage1(:,:,1), resultImage2(:,:,1)] = find_couche_rgb (image(:,:,1));
    //Green
    [resultImage1(:,:,2), resultImage2(:,:,2)] = find_couche_rgb (image(:,:,2));
    //Blue
    [resultImage1(:,:,3), resultImage2(:,:,3)] = find_couche_rgb (image(:,:,3));
endfunction

function [resultRGB1, resultRGB2] =  find_couche_rgb(rgb)
    rgb = double (rgb);
    resultRGB1 = floor (rgb/16)*16;
    resultRGB2 = (rgb - resultRGB1)*16;
    resultRGB1 = uint8 (resultRGB1);
    resultRGB2 = uint8 (resultRGB2);
endfunction

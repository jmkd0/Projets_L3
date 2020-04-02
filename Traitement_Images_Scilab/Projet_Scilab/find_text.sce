function [text] = find_Text (image)
    text = [];
    i = 1;
    j = 1;
    image = double (image);
    bits1 = image(i,j,1)-floor (image(i,j,1)/16)*16;
    bits2 = image(i,j,3)-floor (image(i,j,3)/16)*16;
    bits  = bits2*16 + bits1;
    while (bits <> 128) //Si on n'est pas encore tombé sur le label de fin
        text = [text, bits];
        j = j+1;
        if j > size (image,1)
            i = i+1;
            j = 1;
        end
        bits1 = image(i,j,1)-floor (image(i,j,1)/16)*16;
        bits2 = image(i,j,3)-floor (image(i,j,3)/16)*16;
        bits  = bits2*16 + bits1;
    end
    text = char (text);
endfunction

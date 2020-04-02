/*
    On parcours l'image et 
    Tant qu'on n'est pas en fin de caractères
    Si on n'est pas en fin de text On remplace les quatres derniers bits du bleue par les quatres premiers bit du caractere pui
    On remplace les quatres derniers bits du rouge par les derniers bit du caractere 
    En fin de text on crée un label de fin pour reconnaitre la fin plus tard, prenons le caractere qui a pour code ascii 128 et donc     n'est pas parmi les caracteres habituels
*/
function [resultImage] = hide_Text(hiderImage, hiddenText)
    hiderImage = double (hiderImage);
    resultImage = hiderImage;
    k = 0;
    hiddenText = double (hiddenText);
    if size(hiddenText) < size(hiderImage,1)*size(hiderImage,2)
        for i = 1 : size(hiderImage,1)
            for j = 1 : size(hiderImage,2)
                k = k+1;
                if k <= size(hiddenText,2) 
                    resultImage(i,j,1) = floor (hiderImage(i,j,1)/16)*16 + hiddenText(k) - floor (hiddenText(k)/16)*16; 
                    resultImage(i,j,3) = floor (hiderImage(i,j,3)/16)*16 + floor (hiddenText(k)/16); 
                end
                if k == size(hiddenText,2)+1 
                    resultImage(i,j,1) = floor (hiderImage(i,j,1)/16)*16 + 128 - floor (128/16)*16;
                    resultImage(i,j,3) = floor (hiderImage(i,j,3)/16)*16 + floor (128/16);
                end 
            end 
        end
    else
         disp ('Text trop long');
    end
   resultImage = uint8 (resultImage);
endfunction

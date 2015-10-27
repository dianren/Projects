%%
% Reading and displaying image %
he = imread('paintingtest.jpg');
imshow(he), title('LISS 4 + CARTOSAT 1 fused image');

% Creating color transformation from sRGB to L*a*b %
 cform = makecform('srgb2lab');
 % Applying above color transform to the sRGB image %
lab_he = applycform(he,cform);
% Converting into double %
ab = double(lab_he(:,:,2:3));
% obtaining rows and columns of transformed image %
nrows = size(ab,1);
ncols = size(ab,2);
% Reshaping image taking each value column wise %
ab = reshape(ab,nrows*ncols,2);
% No of clusters to be created with five iterations %
nColors = 6;
[cluster_idx cluster_center] = kmeans(ab,nColors,'distance','sqEuclidean', 'Replicates',5);
% Reshaping and showing the clusters %
pixel_labels = reshape(cluster_idx,nrows,ncols);
imshow(pixel_labels,[]), title('image labeled by cluster index');

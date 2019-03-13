evolve = load('evolve');
evolve1 = load('evolve1');
evolve2 = load('evolve2');

nsimul = 1;
%groups::
magnets = zeros(nsimul,30,2); %angle,type
vertices = zeros(nsimul,20,2); %angle,angle,angle,energy
doublevertices = zeros(nsimul,30,3); %anglex5,energy,type
faces = zeros(nsimul,12,7); %anglex5,typex5,orientation,energy,

for i = 1:nsimul
  angles = evolve(i,2:31);
  dlmwrite('finalangles.in',angles,'delimiter',' ');
  system('debug/Analysis');
  %should create 4 temp files: Magnet, Vertex, DVertex, Faceparameters
 % tempmagnet = load('Magnet')
%   tempvertex = load('Vertex');
%   tempdvertex = load('DVertex');
%   tempface = load('Faceparameters');
%   vertices(i,:,:) = tempvertex;
%   doublevertices(i,:,:) = tempdvertex;
%   faces(i,:,:) = tempface;
end


%save('data/magnets',vertices)
% save('data/vertices','vertices')
% save('data/doublevertices','doublevertices')
% save('data/faces','faces')

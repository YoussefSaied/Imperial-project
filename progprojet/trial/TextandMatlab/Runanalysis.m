%1. load files made by simulationt
%2. run analysis on a single line from data saved as finalanalysis.in
%3. save the files in the temp folder, load them and add to array of total
%data
%4. indices

%has to be named correctly.. include time
nsimul = 1;

%% EVOLVE

evolve = load('data/evolve/angles'); %time, energy, cor, anglesx30
magnets = zeros(nsimul,30,2); %angle, type
vertices = zeros(nsimul,20,2); %,energy, oddoneout
doublevertices = zeros(nsimul,30,3); %centralmag_index, energy, strengthdet
faces = zeros(nsimul,12,7); %index5,orientation,energy,
for i = 1:nsimul
  angles = evolve(i,4:33);
  magnets(i,:,1) = angles;
  dlmwrite('finalangles.in',angles,'delimiter',' ');
  system('debug/Analysis');
  %should create 4 temp files: Magnet, Vertex, DVertex, Faceparameters
  tempmagnet = load('Magnet');
  tempvertex = load('Vertex');
  tempdvertex = load('DVertex');
  tempface = load('Faceparameters');
  for j = 1:30
      k = tempdvertex(j,1); %index cm
      type = tempdvertex(j,3); %type
      magnets(i,k,2) = type;
  end
  vertices(i,:,:) = tempvertex;
  doublevertices(i,:,:) = tempdvertex;
  faces(i,:,:) = tempface;
end
save('data/evolve/magnets','magnets')
save('data/evolve/vertices','vertices')
save('data/evolve/doublevertices','doublevertices')
save('data/evolve/faces','faces')

%% EVOLVE1

evolve1 = load('data/evolve1/angles'); %time, energy, cor, anglesx30
magnets = zeros(nsimul,30,2); %angle, type
vertices = zeros(nsimul,20,2); %,energy, oddoneout
doublevertices = zeros(nsimul,30,3); %centralmag_index, energy, strengthdet
faces = zeros(nsimul,12,7); %index5,orientation,energy,
for i = 1:nsimul
  angles = evolve1(i,4:33);
  magnets(i,:,1) = angles;
  dlmwrite('finalangles.in',angles,'delimiter',' ');
  system('debug/Analysis');
  %should create 4 temp files: Magnet, Vertex, DVertex, Faceparameters
  tempmagnet = load('Magnet');
  tempvertex = load('Vertex');
  tempdvertex = load('DVertex');
  tempface = load('Faceparameters');
  for j = 1:30
      k = tempdvertex(j,1); %index cm
      type = tempdvertex(j,3); %type
      magnets(i,k,2) = type;
  end
  vertices(i,:,:) = tempvertex;
  doublevertices(i,:,:) = tempdvertex;
  faces(i,:,:) = tempface;
end
save('data/evolve1/magnets','magnets')
save('data/evolve1/vertices','vertices')
save('data/evolve1/doublevertices','doublevertices')
save('data/evolve1/faces','faces')


%% EVOLVE2

evolve = load('data/evolve2/angles'); %time, energy, cor, anglesx30
magnets = zeros(nsimul,30,2); %angle, type
vertices = zeros(nsimul,20,2); %,energy, oddoneout
doublevertices = zeros(nsimul,30,3); %centralmag_index, energy, strengthdet
faces = zeros(nsimul,12,7); %index5,orientation,energy,
for i = 1:nsimul
  angles = evolve2(i,4:33);
  magnets(i,:,1) = angles;
  dlmwrite('finalangles.in',angles,'delimiter',' ');
  system('debug/Analysis');
  %should create 4 temp files: Magnet, Vertex, DVertex, Faceparameters
  tempmagnet = load('Magnet');
  tempvertex = load('Vertex');
  tempdvertex = load('DVertex');
  tempface = load('Faceparameters');
  for j = 1:30
      k = tempdvertex(j,1); %index cm
      type = tempdvertex(j,3); %type
      magnets(i,k,2) = type;
  end
  vertices(i,:,:) = tempvertex;
  doublevertices(i,:,:) = tempdvertex;
  faces(i,:,:) = tempface;
end
save('data/evolve2/magnets','magnets')
save('data/evolve2/vertices','vertices')
save('data/evolve2/doublevertices','doublevertices')
save('data/evolve2/faces','faces')



    





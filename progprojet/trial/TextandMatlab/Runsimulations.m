%% Simulations %%
repertoire = '';
executable = 'debug/simulationt';
input = 'configuration.in';

%number of simulations to be run
nsimul = 5;
filename = 'magnetangles';

tic
eval(sprintf('!%s %s %s=%.15g output=%s',executable, input, 'nsimul', nsimul, filename));
disp('Done.')
toc

%%Data Grouping%%
data = load('magnetangles');

%groups::
magnets = zeros(nsimul,30,2); %angle,type
vertices = zeros(nsimul,20,4); %angle,angle,angle,energy
doublevertices = zeros(nsimul,30,7); %anglex5,energy,type
faces = zeros(nsimul,12,12); %anglex5,typex5,orientation,energy,

for i in 1:nsimul
  angles = data(i,:);
  %make temp file called 'finalangles.in' which contains data from this run? - might be the only way to do it

  eval(sprintf( 'Analysis.cc'));
  %should create 4 temp files: Magnet, Vertex, DVertex, Faceparameters
  tempmagnet = load('temp/Magnet')
  tempvertex = load('temp/Vertex');
  tempdvertex = load('temp/DVertex');
  tempface = load('temp/Faceparameters');
  vertices(i,:,:) = tempvertex;
  doublevertices(i,:,:) = tempdvertex;
  faces(i,:,:) = tempface;
end


save('data/magnets',vertices)
save('data/vertices',vertices)
save('data/doublevertices',doublevertices)
save('data/faces',faces)

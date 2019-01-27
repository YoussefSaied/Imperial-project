% Ce script Matlab automatise la production de resultats
% lorsqu'on doit faire une serie de simulations en
% variant un des parametres d'entree.
% 
% Il utilise les arguments du programme (voir ConfigFile.h)
% pour remplacer la valeur d'un parametre du fichier d'input
% par la valeur scannee.
%
set(groot, 'defaultAxesTickLabelInterpreter','latex');
set(groot, 'defaultLegendInterpreter','latex');
set(groot, 'defaultTextInterpreter', 'latex');
set(groot, 'defaultAxesFontSize', 18);

%% Parametres %%
%%%%%%%%%%%%%%%%

repertoire = './'; % Chemin d'acces au code compile
executable = 'Exercice7'; % Nom de l'executable
input = 'configuration3.in'; % Nom du fichier d'entree

nsimul = 100; % Nombre de simulations a faire

% Indiquer ici les valeurs des parametres a scanner :
Npoints = zeros(1,nsimul);
for i=1:nsimul
    Npoints(i)= 500*2^i;
end
tfin = linspace(5,65,nsimul);
%Npoints = linspace(300,2500,nsimul);

L= 5;
u= 2;
%r
r= linspace(20e3,500e3,nsimul);
omega = linspace(0,7*pi*u/2/L,nsimul);
CFL= linspace(0.1,1.5,nsimul);
% Selectionner ici le parametre a scanner
 paramstr = 'r';
 param = r;


%% Simulations %%

output = cell(1, nsimul);

tic
for i = 1:nsimul
    filename = [paramstr, '=', num2str(param(i))];
    output{i} = [filename, '_fixe.out'];
    %output{i} = ['N/',filename, '.out'];
    eval(sprintf('!%s%s %s %s=%.15g output=%s', repertoire, executable, input, paramstr, param(i), output{i}));
    % Variante pour scanner Nx et Ny en meme temps:
    % eval(sprintf('!%s%s %s %s=%.15g %s=%.15g output=%s', repertoire, executable, input, [paramstr,'x'], param(i), [paramstr,'y'], param(i), output{i}));
    disp('Done.')
end
toc

%% Analyse %%
%%%%%%%%%%%%%

if(strcmp(paramstr,'Npoints'))
    var = zeros(1,nsimul);
% Parcours des resultats de toutes les simulations
L=5;

dataanal=  load([[output{nsimul}],'_f']);
tanal= dataanal(:,1);
t8 = length(tanal)*0.814;
fanal=dataanal(floor(t8),2:end);
dxanal= 2*L / (Npoints(nsimul)-1);
dataanal = load([[output{nsimul}],'_u']);
xanal= dataanal(:,1);
figure 
hold on
%plot(xanal,fanal)
for i = 1:nsimul
    fichier = [output{i}];
    dxi = 2*L / (Npoints(i) -1);
    data = load([fichier,'_f']);
    t = data(:,1);
    t8 = length(t)*0.814; % calcul d'indice pout t = 8s
    f = data(floor(t8),2:end);
    data = load([fichier,'_u']);
    x= data(:,1);
    %plot(x,f)
    for j = 1:length(f)
        %fanal(j) =  sin(j*dx + 5 + u*3.14 );
        %if floor(j*(dxi/dxanal)) == 0; a=1; end
        %if floor(j*(dxi/dxanal)) ~= 0 && floor(j*(dxi/dxanal)) > length(fanal);  a=length(fanal); end
       % if floor(j*(dxi/dxanal)) ~= 0 && floor(j*(dxi/dxanal)) <= length(fanal);  a=floor(j*(dxi/dxanal));
            
        if floor(j*(dxi/dx_analytique)) == 0; a=1; end
        if floor(j*(dxi/dx_analytique)) ~= 0 && floor(j*(dxi/dx_analytique)) > length(f_analytique);  a=length(f_analytique); end
        if floor(j*(dxi/dx_analytique)) ~= 0 && floor(j*(dxi/dx_analytique)) <= length(f_analytique);  a=floor(j*(dxi/dx_analytique));  end
        var(i) = var(i) + (f_analytique(a) - f(j))^2;
        %variable(j) = abs(fanal(a) - f(j));
        %variable2(j) = j*(dxi/dxanal);
    
    end
    
end
end

if(strcmp(paramstr,'omega') || strcmp(paramstr,'tfin') )
   Emax= zeros(1,nsimul);
   for i=1:nsimul
       fichier = [output{i}];
       data = load([fichier,'_E']);
       Emax(i) = max(data(:,2));
   end
end
if(strcmp(paramstr,'r'))
    for i = 1:nsimul
        fichier = [output{i}];
        data = load([fichier,'_f']);
        f = data(:,2:end);
        maxA(i)=max(f(floor(size(f,1)*(0.5+r(i)/10e5)),:));
    end
end
if(strcmp(paramstr,'CFL'))
    for i = 1:nsimul
        fichier = [output{i}];
        data = load([fichier,'_f']);
        f = data(:,2:end);
        maxA(i)=max(max(f));
    end
end
%% Figures Npoints

var2 = sqrt(var);

Fit = LinearModel.fit(dx,var2)
p = polyfit(dx,var2,1)
pv = polyval(p,dx);

 figure
    dx= 2*L*ones(1,nsimul);
    dx= dx./ (Npoints- ones(1,nsimul));
    plot(dx,var2,'k+')
    hold on
    plot(dx,pv,'--','color','k');
    xlabel('$\Delta x$ [m]')
    ylabel('Difference de forme [m]')
    grid on
 figure
    hold on
    plot(Npoints,sqrt(var),'k-+')
    xlabel('N []')
    ylabel('Difference en forme [m]')
    grid on

%% Figures omega    
if(strcmp(paramstr,'omega'))
figure
    hold on
    plot(omega,Emax,'k-+')
    xlabel('omega [$s^{-1}$]')
    ylabel('MaxE [J]')
    grid on
end
%% Ex7.2b: Figures tfin
if(strcmp(paramstr,'tfin'))
figure
    hold on
    plot(tfin,Emax,'k-+')
    xlabel('tfin [s]')
    ylabel('MaxE [J]')
    grid on
end
%% Ex7.3c: amplitude apres r
if(strcmp(paramstr,'r'))
figure
    hold on
    plot(r,maxA,'k-+')
    xlabel('r [m]')
    ylabel('MaxAmplitude [m]')
    grid on
end
%% Beta
if(strcmp(paramstr,'CFL'))
figure
    hold on
    plot(CFL,log(maxA),'k-+')
    xlabel('$\beta$ []')
    ylabel('log(MaxAmplitude) []')
    grid on
end

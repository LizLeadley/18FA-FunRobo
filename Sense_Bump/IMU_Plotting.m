%% Load, Plot, and Compare csv Datasets from the IMU
% Two functions included: loadAndPlot, and loadAndCompare. Each has its own
% section below. Anything that is not double-commented can be ctrl+r
% uncommented and run (assuming you have matching file names)

% files have to be in same directory as this, otherwise you have to give a
% full file path. Make sure to 'Change Folder' into where they all live.

%% Load and Plot These things:

% % loadAndPlot takes a file name of a csv from BumpToGraph arduino code,
% % and plots each reading across time with labels.

loadAndPlot('test.txt')

% % Round 1 of testing
% loadAndPlot('front.txt')
% loadAndPlot('right.txt')
% loadAndPlot('back.txt')
% loadAndPlot('left.txt')
% loadAndPlot('top.txt')


%% Load and Compare things

% % loadAndCompare takes a matrix of file names, each in "", such as
% % ["file1.txt", "file2.txt"], of any size (i.e. anywhere from 1 to a
% % jillion files, so long as they are in format)

% % The second argument determines which part of the data is plotted:
% % whichToPlot argument of loadAndCompare uses the following mapping:
% % 1: Time (ms);      2: aX(m/s^2);    3: aY(m/s^2);    4: aZ(m/s^2)
% % 5: Pitch(deg);     6: Roll(deg);    7: Heading(deg)

% loadAndCompare(["right.txt", "right2.txt", "right3.txt"], 2)
% loadAndCompare(["left.txt", "left2.txt", "left3.txt"], 2)

%% I made it a function that takes a file name as input, and plots the csv
function [] = loadAndPlot(fileName)
%% Loading data
clear Timems aXms2 aYms2 aZms2 Pitchdeg Rolldeg Headingdeg Calibrationstatus
dataMat = csvread(fileName, 2, 0);
Timems = dataMat(:,1);
aXms2 = dataMat(:,2);
aYms2 = dataMat(:,3);
aZms2 = dataMat(:,4);
Pitchdeg = dataMat(:,5);
Rolldeg = dataMat(:,6);
Headingdeg = dataMat(:,7);

%% Plotting it
figure; hold on;

yyaxis left
plotvsTime(Timems, aXms2, 'r')
plotvsTime(Timems, aYms2, 'g')
plotvsTime(Timems, aZms2, 'b')
ylabel ('Acceleration (m/s^2)')

yyaxis right
plotvsTime(Timems, Pitchdeg, 'm')
plotvsTime(Timems, Rolldeg, 'y')
% Converting heading so it doesn't flip between 0 and 360 abruptly
Headings = abs(Headingdeg-180);
plotvsTime(Timems, Headings, 'c')
%Heading is officially worthless. 
ylabel ('Degrees')

xlabel ('Time (ms)')
title (fileName) %'Bump Accel v Time'
legend ('X', 'Y', 'Z', 'Pitch', 'Roll', 'Heading', 'Location', 'Best')

%% Plotting function to avoid retyping
function [] = plotvsTime(Timems, var, color)
    plot((Timems-Timems(1))/1000, var-var(1), color, 'LineStyle', '-', 'LineWidth', 1);
end

end


%% Another function, to compare one value across several three csvs
function [] = loadAndCompare(fileNameMatrix, whichToPlot)
%% Loading and plot each file
figure; hold on;
% loadPlotSingle(fileName1, whichToPlot)
% loadPlotSingle(fileName2, whichToPlot)
% loadPlotSingle(fileName3, whichToPlot)
for temp = fileNameMatrix
   loadPlotSingle(temp, whichToPlot)
end

%% Label the Plot
varNames = ["Timems"; "aXms2"; "aYms2"; "aZms2"; "Pitch"; "Roll"; "Heading"];
ylabel (varNames(whichToPlot,:))
xlabel ('Time (ms)')
title (varNames(whichToPlot,:))
legend (fileNameMatrix)

%% Plotting function to avoid retyping
function [] = loadPlotSingle(fileName, whichToPlot)
    dataMat = csvread(fileName, 2, 0);
    Timems = dataMat(:,1);
    var = dataMat(:,whichToPlot);
    plot((Timems-Timems(1))/1000, var-var(1), 'LineStyle', '-', 'LineWidth', 1);
end
end
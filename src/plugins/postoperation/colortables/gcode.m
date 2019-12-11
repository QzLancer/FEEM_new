dirOutput=dir(fullfile('.','*.txt'));
fp1 = fopen('code.cpp','w');
for i=1:size(dirOutput,1)
   fp = fopen(dirOutput(i).name)
   line = fgets(fp);
   cTab = fscanf(fp,'%f %f %f \n',[3 Inf])';
   fn =  strsplit(dirOutput(i).name,'.');
   fn = fn{1};
   fprintf(fp1,['case ',fn,':\n']);
   for j = 1:size(cTab,1)
      fprintf(fp1,'cTab[n++].setRgbF(%f,%f,%f);\n',cTab(j,1),cTab(j,2),cTab(j,3)) ;
   end
   fprintf(fp1,'break;\n');
   fprintf(fp1,'\n');
   fclose(fp);
end

fclose(fp1);
fp1 = fopen('code1.cpp','w');
for i=1:size(dirOutput,1)
   fp = fopen(dirOutput(i).name)
   line = fgets(fp);
   cTab = fscanf(fp,'%f %f %f \n',[3 Inf])';
   fn =  strsplit(dirOutput(i).name,'.');
   fn = fn{1};
   fprintf(fp1,['case Plot::',fn,':\n']);
   fprintf(fp1,'{\n');
   fprintf(fp1,['d_spectrogram->setColorMap( new Postoperation::PF_ColorMap(Postoperation::PF_ColorMap::',fn,'));\n']);
   fprintf(fp1,['axis->setColorMap( zInterval, new Postoperation::PF_ColorMap(Postoperation::PF_ColorMap::',fn,'));\n']);
   fprintf(fp1,'break;\n');
   fprintf(fp1,'}\n');   
   fprintf(fp1,'\n');
end
fclose(fp1);
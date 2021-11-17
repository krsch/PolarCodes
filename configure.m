!git submodule update --init
%if ~isfolder('build-mat')
    %mkdir('build-mat')
%end
%wd = cd;
%cd build-mat
cmd = ['cmake -Bbuild-mat -DMatlab_ROOT_DIR="' matlabroot '" -DCMAKE_BUILD_TYPE=RelWithDebInfo -S.'];
if ispc
    cmd = [cmd ' -A x64']
elseif isunix && ~ismac
    cmd = [cmd ' -G Ninja']
end
system(cmd, '-echo')
%cd(wd);

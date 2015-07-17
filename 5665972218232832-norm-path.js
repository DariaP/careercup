/*
Given a string representing relative path write a function which normalizes this path (i.e. replaces ".."). 
Example: 
input: \a\b\..\foo.txt 
output: \a\foo.txt
*/

function normalize(path) {
  var normFolders = path();

  path.split("\\").forEach(
    function(folder) {
      if (folder === "..") {
        normFolders.up();
      } else if (folder !== "") {
        normFolders.down(folder);
      }
    }
  );

  function path() {
    var _folders = {};
    return {
      up: function() {
        if (_folders.length !== 0) {
          _folders.pop();
        } else {
          throw "Invalid path"
        }
      },
      down: function(folderName) {
        _folders.push()
      }
    }
  }
  
}
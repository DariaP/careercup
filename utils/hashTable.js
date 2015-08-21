
function hashTable() {
  var values = {},
      keys = [];

  return {
    put: function(key, value) {
      if (keys.indexOf(key) === -1) {
        keys.push(key);
      }
      values[key] = value;
    },

    size: function() {
      keys.length;
    },

    has: function(key) {
      return (keys.indexOf(key) !== -1);
    }
  };
}

module.exports = hashTable;
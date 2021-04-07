$(buttonReady).click(e => {
   buttonReady.classList.add('dn');
   buttonNotReady.classList.remove('dn');
   
   $('main').addClass('dn');
   $('.game').removeClass('dn');
});
$(buttonNotReady).click(e => {
   buttonNotReady.classList.add('dn');
   buttonReady.classList.remove('dn');
});


class Ground {
   /**
    * Consist logic of ground block
    * @param {string} startFieldName image name of field
    */
   constructor(startFieldName) {
      this.el = document.querySelector('.ground');

      this.rows = Array.from(this.el.querySelectorAll('.row'));
      this.grid = this.rows.map(row => Array.from(row.querySelectorAll('.ground__cell')));
      
      this.fieldName = startFieldName;
      this.field = startFieldName;
   }

   /**
    * @param {string} valueName the name of imageField_{name} image
    */
   set field(valueName) {
      $('.ground__cell').css('background-image', `url("${window[`imageField_${valueName}`].src}")`);
      this.figure = this.figureName;
      this.fieldName = valueName;
   }
   
   /**
    * Puts figure of color to cell
    * @param {number} posX 
    * @param {number} posY 
    * @param {string} color 
    */
   put(posX, posY, color) {
      const $figure = this.getFigure(posX, posY);
      $figure.css('background-image', `url("${window[`imageFigure_${color}`].src}")`).parent().css('background-image', '');
   }
   
   /**
    * Removes figure from cell
    * @param {number} posX 
    * @param {number} posY 
    */
   erase(posX, posY) {
      const $figure = this.getFigure(posX, posY);
      $figure.css('background-image', '').parent().css('background-image', window[`imageField_${this.fieldName}`].src);

   }
   
   getFigure(posX, posY) {
      return $(this.grid[posY][posX].firstElementChild);
   }
}


const ground = new Ground('pink');
turnIndicator.src = window[`imageFigure_${'yellow'}`].src;

const start = {
   pink: [
      [0, 0],
      [1, 0],
      [1, 1],
   ],
   yellow: [
      [2, 0],
      [3, 1],
      [2, 2],
   ],
   orange: [
      [1, 2],
      [3, 2],
      [4, 2],
   ],
};

for (let color in start) {
   const positions = start[color];
   for (let [ posX, posY ] of positions) {
      ground.put(posX, posY, color);
   }
}
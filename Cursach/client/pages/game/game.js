// STOP: Before game

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

$('.figure-select__cell').click(e => {
   const $currentTarget = $(e.currentTarget),
      sel = 'figure-select__cell_selected',
      otherSel = 'figure-select__cell_other-selected';
   if ($currentTarget.hasClass(otherSel)) return;
   if ($currentTarget.hasClass(sel)) {
      $currentTarget.removeClass(sel);
      return;
   }

   const $selected = $('.'+sel);
   $selected.removeClass(sel);
   $currentTarget.addClass(sel);
   
   if ($selected.length == 0)
      sendFigureSelect(e.currentTarget.dataset.type);
   else
      sendFigureChange($selected[0].dataset.type, e.currentTarget.dataset.type);
});



// STOP: Game process

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

const start = {
   pinkX: [
      [0, 0],
      [1, 0],
      [1, 1],
   ],
   yellowO: [
      [2, 0],
      [3, 1],
      [2, 2],
   ],
   orangeP: [
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


function otherFigureSelect(figureName) {
   
}
function otherFigureUnselect(figureName) {

}
function otherFigureChange(oldFigureName, newFigureName) {
   
}

getGameSid(sid => {
   sidElement.textContent = sid;
});

getConnectionCount(count => {
   updateConnectionCount(count);
})

function updateConnectionCount(count) {
   connectionCount.textContent = count;
   
   count = +count;

   let countWord;
   switch (count) {
      case 1:
         countWord = 'игрок'; break;
      case 2:
      case 3:
      case 4:
         countWord = 'игрока'; break;
      case 5:
         countWord = 'игроков'; break;
   };
   connectionCountWord.textContent = countWord;
}
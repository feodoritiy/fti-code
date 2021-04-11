class SliderEventData {
   /**
    * Store data of slider event
    * @param {HTMLElement} slider 
    * @param {HTMLElement} cell 
    * @param {String} direction 
    * @param {String} i 
    * @param {Number} cellCount 
    */
   constructor (slider, cell, direction, i, cellCount) {
      this.slider = slider;
      this.cell = cell;
      this.direction = direction;
      this.i = i;
      this.cellCount = cellCount;
   }
}

$('.slider__arrow_right').click(e => {
   const $slider = $(e.target).parents('.slider'),
   slider = $slider[0];

   scrollSlider($slider, +slider.dataset.current + 1, 'right');
});
$('.slider__arrow_left').click(e => {
   const $slider = $(e.target).parents('.slider'),
   slider = $slider[0];

   scrollSlider($slider, +slider.dataset.current - 1, 'left');
});

function scrollSlider($slider, i, direction = 'force') {
   const slider = $slider[0],
      cellCount = $slider.find('.slider__cell').length,
      cellWidth = $slider.find('.slider__cell')[0].getBoundingClientRect().width
      sliderContent = $slider.find('.slider__content')[0];

   if (i < 0) return;
   if (i > cellCount - 1) return;
   
   sliderContent.style.left = -1 * cellWidth * i + 'px';
   slider.dataset.current = i;
   
   onSliderChange(new SliderEventData(
      slider, 
      $slider.find('.slider__cell')[slider.dataset.current],
      direction,
      slider.dataset.current,
      cellCount
   ));
}

/**
 * Handle and process slider changes
 * @param {SliderEventData} eventData Data of slider event
 * @returns {void}
 */
function onSliderChange(eventData) {
   const slider = eventData.slider,
      $footer = $('.slider__footer', slider),
      $currButton = $('button:not(dn)', $footer);

   $currButton.addClass('dn');
   $(`.button_${eventData.cell.dataset.state}`, $footer).removeClass('dn');
   
   if (slider.dataset.type == 'figure') {
      fitting.onFigureSliderChange(eventData);
   } else if (slider.dataset.type == 'field') {
      fitting.onFieldSliderChange(eventData);
   }
}

$('.fitting__amount').click(e => e.preventDefault());
$('.fitting__cell').css('background-image', `url("${imageField_pink.src}")`);
$('.fitting__figure').css('background-image', `url("${imageFigure_pink.src}")`).parent().css('background-image', '');

class Fitting {
   /**
    * Consist logic of fitting block
    * @param {string} startFigureName image name of figure
    * @param {string} startFieldName image name of field
    */
   constructor(startFigureName, startFieldName) {
      this.el = document.querySelector('.fitting');
      
      this.fieldName = startFieldName;
      this.figureName = startFigureName;

      this.field = startFieldName;
      this.figure = startFigureName;
   }

   /**
    * @param {string} valueName the name of imageFigure_{name} image
    */
   set figure(valueName) {
      $('.fitting__figure').css('background-image', `url("${window[`imageFigure_${valueName}`].src}")`).parent().css('background-image', '');
      this.figureName = valueName;
   }
   
   /**
    * @param {string} valueName the name of imageField_{name} image
    */
   set field(valueName) {
      $('.fitting__cell').css('background-image', `url("${window[`imageField_${valueName}`].src}")`);
      this.fieldName = valueName;
   }
   
   /**
    * Fires when slider with figures change value
    * @param {SliderEventData} eventData 
    */
   onFigureSliderChange(eventData) {
      this.figure = eventData.cell.dataset.value;
   }

   /**
    * Fires when slider with fields change value
    * @param {SliderEventData} eventData 
    */
   onFieldSliderChange(eventData) {
      this.field = eventData.cell.dataset.value;
      this.figure = this.figureName;
   }
}

const fitting = new Fitting('pink', 'pink');


// STOP: Server connection & logic

async function syncServerData () {
   const res = await new Promise(res => getShop(res));
   let { id: id, shop: shop, amount: amount } = res;
   shop = JSON.parse(shop);

   console.log('id:', id, 'shop:', shop, 'amount:', amount);
   
   amountEl.textContent = amount;
   
   const sliderFigure = document.querySelector('.slider[data-type="figure"]'),
      sliderField = document.querySelector('.slider[data-type="field"]'),
      cellsFigure = Array.from(sliderFigure.querySelectorAll('.slider__cell')),
      cellsField = Array.from(sliderField.querySelectorAll('.slider__cell'));
   
   for (const figure of cellsFigure) {
      figure.dataset.state = shop.figure[figure.dataset.value];
   }
   for (const field of cellsField) {
      field.dataset.state = shop.field[field.dataset.value];
   }
   
   scrollSlider($(sliderFigure), cellsFigure.findIndex(cell => cell.dataset.state == 'selected'));
   scrollSlider($(sliderField), cellsField.findIndex(cell => cell.dataset.state == 'selected'));
}

syncServerData();
searchForm = document.querySelector('.search-form');

document.querySelector('#search-btn').onclick = () =>{
    searchForm.classList.toggle('active');
}

window.onscroll = () =>{

    searchForm.classList.remove('active');

    if(window.scrollY > 80){
        document.querySelector('.header .header-2').classList.add('active');
    }else{
        document.querySelector('.header .header-2').classList.remove('active');
    }
}

window.onload = () =>{
    if(window.scrollY > 80){
        document.querySelector('.header .header-2').classList.add('active');
    }else{
        document.querySelector('.header .header-2').classList.remove('active');
    }
}


// Allows the books to swipe horizontally across the Screen
var swiper = new Swiper(".books-slider", {
loop:true,
centeredSlides: true,
autoplay: {
    delay:9500,
    disableOnInteraction: false,
},

breakpoints:{
    0:{
        slidesPerView:1,
    },

    768: {
        slidesPerView:2,
    },

    1024: {
        slidesPerView: 3,
    },
  },

});
// End of Swiper

// Swipes the books in a 'Featured' Section of the Page
var swiper = new Swiper(".featured-slider", {
    spaceBetween:10,
    loop:true,
    centeredSlides: true,
    autoplay: {
        delay:9500,
        disableOnInteraction: false,
    },
    navigation:{
        nextE1: ".swiper-button-next",
        prevE1: ".swiper-button-prev",
    },
    breakpoints:{
        0:{
            slidesPerView:1,
        },
    
        450:{
            slidesPerView:2,
        },

        768: {
            slidesPerView:3,
        },
    
        1024: {
            slidesPerView: 4,
        },
      },
    
    });
    // End of Swiper Section 
const express = require('express');
const router = express.Router();

const Board = require('../models/board');

// router.<http method>
router.get('/', function (req, res, next) {
  const boardList = Board.getBoardList();
  res.render(
    "board/boardList",
    { boardList: boardList }
  );
});



module.exports = router;
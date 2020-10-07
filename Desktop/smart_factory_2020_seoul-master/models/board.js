let Board = [
  {
    id: 1,
    title: "게시글1",
    content: '내용1',
    author: '신윤수',
    createdAt: '2020-08-19 12:00:00'
  },
  {
    id: 2,
    title: "게시글2",
    content: '내용2',
    author: '신윤수',
    createdAt: '2020-08-19 12:00:00'
  },
  {
    id: 3,
    title: "게시글3",
    content: '내용3',
    author: '신윤수',
    createdAt: '2020-08-19 12:00:00'
  }
]

module.exports = {
  getBoardList: () => {
    return Board;
  }
}
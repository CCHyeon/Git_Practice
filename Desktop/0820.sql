SELECT *
FROM Customers
WHERE CustomerId IN(
	SELECT distinct CustomerID
	FROM Orders
	WHERE Freight >= 100;
)
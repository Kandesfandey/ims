import React from "react";
import { Home, Items, User, New } from "./pages";
import { itemInputs } from "./formSource";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import Login from "./pages/login";

function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/">
          <Route index element={<Home />} />
          <Route path="/items">
            <Route index element={<Items />} />
            <Route path="new" element={<New inputs={itemInputs} />} />
            <Route path=":itemId" element={<User />} />
          </Route>
          <Route path="/login">
            <Route index element={<Login />} />
          </Route>
        </Route>
      </Routes>
    </BrowserRouter>
  );
}

export default App;

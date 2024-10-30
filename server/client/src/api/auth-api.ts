import User from "@/types/user";
import axios from "axios";

export async function login(username: string, password: string) {
    const response = await axios.post<User>(
        `/auth/login`,
        {
            username: username,
            password: password,
        }
    );

    return response.data;
}

export async function logout() {
    await axios.post("/auth/logout");
}
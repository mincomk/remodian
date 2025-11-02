FROM node:22-slim AS build
WORKDIR /app
COPY package*.json ./
RUN npm i -D
COPY . .
RUN npm run build

FROM node:22-slim
WORKDIR /app

COPY --from=build /app/dist/index.js .
COPY --from=build /app/package*.json .
COPY --from=build /app/node_modules node_modules

EXPOSE 1713
CMD ["node", "index.js"]

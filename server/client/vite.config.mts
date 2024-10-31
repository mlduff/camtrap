// Plugins
import AutoImport from 'unplugin-auto-import/vite'
import Components from 'unplugin-vue-components/vite'
import Fonts from 'unplugin-fonts/vite'
import Layouts from 'vite-plugin-vue-layouts'
import Vue from '@vitejs/plugin-vue'
import VueRouter from 'unplugin-vue-router/vite'
import Vuetify, { transformAssetUrls } from 'vite-plugin-vuetify'
import { VitePWA } from "vite-plugin-pwa";

// Utilities
import { defineConfig } from 'vite'
import { fileURLToPath, URL } from 'node:url'

// https://vitejs.dev/config/
export default defineConfig({
	plugins: [
		VueRouter({
			dts: 'src/typed-router.d.ts',
		}),
		Layouts(),
		AutoImport({
			imports: [
				'vue',
				{
					'vue-router/auto': ['useRoute', 'useRouter'],
				}
			],
			dts: 'src/auto-imports.d.ts',
			eslintrc: {
				enabled: true,
			},
			vueTemplate: true,
		}),
		Components({
			dts: 'src/components.d.ts',
		}),
		Vue({
			template: { transformAssetUrls },
		}),
		// https://github.com/vuetifyjs/vuetify-loader/tree/master/packages/vite-plugin#readme
		Vuetify({
			autoImport: true,
			styles: {
				configFile: 'src/styles/settings.scss',
			},
		}),
		VitePWA({
			registerType: "autoUpdate",
			includeAssets: ['favicon.ico', 'apple-touch-icon.png', 'mask-icon.svg'],
			manifest: {
				name: "FuzzTrap",
				short_name: "FuzzTrap",
				description: "FuzzTrap camera alarm.",
				theme_color: "#ffffff",
				icons: [
					{
						"src": "/pwa-192x192.png",
						"sizes": "192x192",
						"type": "image/png",
						"purpose": "any"
					},
					{
						"src": "/pwa-512x512.png",
						"sizes": "512x512",
						"type": "image/png",
						"purpose": "any"
					},
					{
						"src": "/pwa-maskable-192x192.png",
						"sizes": "192x192",
						"type": "image/png",
						"purpose": "maskable"
					},
					{
						"src": "/pwa-maskable-512x512.png",
						"sizes": "512x512",
						"type": "image/png",
						"purpose": "maskable"
					}
				],
			},
			devOptions: {
				enabled: true,
				type: "module",
			}
		}),
		Fonts({
			google: {
				families: [{
					name: 'Roboto',
					styles: 'wght@100;300;400;500;700;900',
				}],
			},
		}),
	],
	define: { 'process.env': {} },
	resolve: {
		alias: {
			'@': fileURLToPath(new URL('./src', import.meta.url)),
		},
		extensions: [
			'.js',
			'.json',
			'.jsx',
			'.mjs',
			'.ts',
			'.tsx',
			'.vue',
		],
	},
	server: {
		port: 3000,
		proxy: {
			"/dashboard": {
				target: 'http://127.0.0.1:5000',
				changeOrigin: true
			},
			'/auth': {
				target: 'http://127.0.0.1:5000',
				changeOrigin: true
			},
			"/images": {
				target: "http://127.0.0.1:5000",
				changeOrigin: true
			}
		}
	},
})

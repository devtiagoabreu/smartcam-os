// SmartCam Dashboard — Main Application

const SmartCam = {
    baseUrl: '',
    ws: null,
    connected: false,
    currentPage: 'dashboard',

    init() {
        this.detectBaseUrl();
        this.connectWebSocket();
        this.setupNavigation();
    },

    detectBaseUrl() {
        this.baseUrl = window.location.origin;
    },

    connectWebSocket() {
        const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
        const url = `${protocol}//${window.location.host}/ws`;
        this.ws = new WebSocket(url);

        this.ws.onopen = () => {
            this.connected = true;
            document.getElementById('connection-status').textContent = 'Connected';
            document.getElementById('connection-status').className = 'connected';
        };

        this.ws.onclose = () => {
            this.connected = false;
            document.getElementById('connection-status').textContent = 'Disconnected';
            document.getElementById('connection-status').className = 'disconnected';
            setTimeout(() => this.connectWebSocket(), 3000);
        };

        this.ws.onmessage = (event) => {
            const data = JSON.parse(event.data);
            this.handleEvent(data);
        };
    },

    handleEvent(data) {
        // Dispatched to page-specific handlers
        const event = new CustomEvent('smartcam-event', { detail: data });
        document.dispatchEvent(event);
    },

    setupNavigation() {
        document.querySelectorAll('#main-nav a').forEach((link) => {
            link.addEventListener('click', (e) => {
                e.preventDefault();
                const page = link.dataset.page;
                this.navigate(page);
            });
        });
    },

    navigate(page) {
        this.currentPage = page;
        document.querySelectorAll('#main-nav a').forEach((l) => l.classList.remove('active'));
        document.querySelector(`#main-nav a[data-page="${page}"]`).classList.add('active');
        // Page content loaded by page-specific modules
    },

    async api(method, endpoint, body = null) {
        const options = {
            method,
            headers: { 'Content-Type': 'application/json' },
        };
        if (body) options.body = JSON.stringify(body);
        const response = await fetch(`${this.baseUrl}${endpoint}`, options);
        return response.json();
    },
};

document.addEventListener('DOMContentLoaded', () => SmartCam.init());

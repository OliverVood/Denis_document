<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\View;

	class Menu extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?>
			<div class = "view site menu">
				<div class = "list">
					<a>Home</a>
					<a>Portfolio</a>
					<a>Contacts</a>
				</div>
				<div class = "more">
					<div onclick = "$ui_menu.Open();">
						<div></div>
						<div></div>
						<div></div>
					</div>
				</div>
			</div>
		<?php }

	}
<?php

	namespace Proj\Admin\Templates\Users;

	use Base\Templates\View;

	class Form extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render(): void { ?>
			<div class = "view users form">
				htftgfthf
			</div>
		<?php }

	}
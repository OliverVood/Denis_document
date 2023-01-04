<?php

	namespace Proj\Site\Templates\Catalogs;

	use Base\Templates\View;

	class Certificate extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?>
			<div class = "view catalogs work">
				<h1 class = "glob_tabu">Работа с актами</h1>
				<script>
					let Certificate = new Site.Catalogs.CertificateController('.view.catalogs.work');
				</script>
			</div>
		<?php }

	}